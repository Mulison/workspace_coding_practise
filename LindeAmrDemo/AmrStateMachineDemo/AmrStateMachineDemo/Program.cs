using System;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading;

enum RobotState
{
    Idle,
    NavigateToPickup,
    Pickup,
    NavigateToDropoff,
    Dropoff,
    Completed,
    Error
}

sealed class AppConfig
{
    public RobotConfig Robot { get; set; } = new();
    public StationConfig Stations { get; set; } = new();
}

sealed class RobotConfig
{
    public string Name { get; set; } = "AMR";
    public double SpeedMps { get; set; } = 1.0;
    public int NavTimeoutMs { get; set; } = 2000;
    public int PickupTimeMs { get; set; } = 1000;
    public int DropoffTimeMs { get; set; } = 1000;
    public int MaxRetries { get; set; } = 1;
}

sealed class StationConfig
{
    public Pose Pickup { get; set; } = new();
    public Pose Dropoff { get; set; } = new();
}

sealed class Pose
{
    public string Name { get; set; } = "Station";
    public double X { get; set; }
    public double Y { get; set; }
}

static class Log
{
    public static void Info(string msg) =>
        Console.WriteLine($"{DateTime.Now:HH:mm:ss.fff} [INFO] {msg}");

    public static void Warn(string msg) =>
        Console.WriteLine($"{DateTime.Now:HH:mm:ss.fff} [WARN] {msg}");

    public static void Error(string msg) =>
        Console.WriteLine($"{DateTime.Now:HH:mm:ss.fff} [ERROR] {msg}");
}

sealed class RobotController
{
    private readonly AppConfig _cfg;
    private RobotState _state = RobotState.Idle;

    private int _retryCount = 0;
    private readonly Random _rng = new(7); // deterministic demo

    public RobotController(AppConfig cfg) => _cfg = cfg;

    public void Run()
    {
        Log.Info($"Robot '{_cfg.Robot.Name}' starting. Speed={_cfg.Robot.SpeedMps} m/s, NavTimeout={_cfg.Robot.NavTimeoutMs} ms");

        while (_state is not RobotState.Completed and not RobotState.Error)
        {
            switch (_state)
            {
                case RobotState.Idle:
                    TransitionTo(RobotState.NavigateToPickup);
                    break;

                case RobotState.NavigateToPickup:
                    if (Navigate(_cfg.Stations.Pickup))
                        TransitionTo(RobotState.Pickup);
                    else
                        HandleRetryOrFail("Navigation to Pickup failed");
                    break;

                case RobotState.Pickup:
                    if (DoAction("Pickup", _cfg.Robot.PickupTimeMs))
                        TransitionTo(RobotState.NavigateToDropoff);
                    else
                        HandleRetryOrFail("Pickup action failed");
                    break;

                case RobotState.NavigateToDropoff:
                    if (Navigate(_cfg.Stations.Dropoff))
                        TransitionTo(RobotState.Dropoff);
                    else
                        HandleRetryOrFail("Navigation to Dropoff failed");
                    break;

                case RobotState.Dropoff:
                    if (DoAction("Dropoff", _cfg.Robot.DropoffTimeMs))
                        TransitionTo(RobotState.Completed);
                    else
                        HandleRetryOrFail("Dropoff action failed");
                    break;

                default:
                    _state = RobotState.Error;
                    break;
            }
        }

        if (_state == RobotState.Completed)
            Log.Info("Order completed successfully.");
        else
            Log.Error("Order ended in ERROR state.");
    }

    private void TransitionTo(RobotState next)
    {
        Log.Info($"State: {_state} -> {next}");
        _state = next;
        _retryCount = 0; // reset retries on successful transition
    }

    private void HandleRetryOrFail(string reason)
    {
        _retryCount++;
        if (_retryCount <= _cfg.Robot.MaxRetries)
        {
            Log.Warn($"{reason}. Retry {_retryCount}/{_cfg.Robot.MaxRetries} (param-driven).");
            Thread.Sleep(300); // small backoff
            // stay in same state -> retry
        }
        else
        {
            Log.Error($"{reason}. MaxRetries exceeded -> ERROR.");
            _state = RobotState.Error;
        }
    }

    // Simulated navigation, affected by parameters
    private bool Navigate(Pose target)
    {
        Log.Info($"Navigating to {target.Name} at ({target.X:F1}, {target.Y:F1})...");

        // Simulate travel time based on "distance / speed"
        double dist = Math.Sqrt(target.X * target.X + target.Y * target.Y);
        int travelMs = (int)Math.Clamp(dist / Math.Max(_cfg.Robot.SpeedMps, 0.1) * 700, 200, 5000);

        // Timeout driven by JSON param
        int allowed = _cfg.Robot.NavTimeoutMs;
        Thread.Sleep(Math.Min(travelMs, allowed));

        // Simulate occasional failure (e.g., blocked path), depends on travel vs timeout + RNG
        bool timeout = travelMs > allowed;
        bool randomFail = _rng.NextDouble() < 0.15;

        if (timeout)
        {
            Log.Warn($"Navigation timeout: travelMs={travelMs} > allowed={allowed}");
            return false;
        }

        if (randomFail)
        {
            Log.Warn("Navigation failed due to simulated obstacle/blockage.");
            return false;
        }

        Log.Info("Arrived.");
        return true;
    }

    // Simulated pickup/dropoff
    private bool DoAction(string actionName, int durationMs)
    {
        Log.Info($"{actionName} started (duration={durationMs} ms, param-driven).");
        Thread.Sleep(Math.Clamp(durationMs, 100, 5000));

        // Simulate occasional failure (e.g., lift sensor not triggered)
        bool fail = _rng.NextDouble() < 0.10;
        if (fail)
        {
            Log.Warn($"{actionName} failed due to simulated sensor/actuator condition.");
            return false;
        }

        Log.Info($"{actionName} done.");
        return true;
    }
}

static class Program
{
    static int Main(string[] args)
    {
        try
        {
            var cfg = LoadConfig("appsettings.json");
            ValidateConfig(cfg);

            var controller = new RobotController(cfg);
            controller.Run();
            return 0;
        }
        catch (Exception ex)
        {
            Log.Error($"Fatal: {ex.Message}");
            return 1;
        }
    }

    private static AppConfig LoadConfig(string path)
    {
        if (!File.Exists(path))
            throw new FileNotFoundException($"Config file not found: {path}");

        var json = File.ReadAllText(path);
        var options = new JsonSerializerOptions
        {
            PropertyNameCaseInsensitive = true,
            ReadCommentHandling = JsonCommentHandling.Skip,
            AllowTrailingCommas = true
        };

        var cfg = JsonSerializer.Deserialize<AppConfig>(json, options);
        return cfg ?? throw new InvalidOperationException("Failed to parse config.");
    }

    private static void ValidateConfig(AppConfig cfg)
    {
        if (cfg.Robot.SpeedMps <= 0) throw new ArgumentException("Robot.SpeedMps must be > 0.");
        if (cfg.Robot.NavTimeoutMs < 200) throw new ArgumentException("Robot.NavTimeoutMs too small.");
        if (cfg.Robot.MaxRetries < 0) throw new ArgumentException("Robot.MaxRetries must be >= 0.");
        if (string.IsNullOrWhiteSpace(cfg.Stations.Pickup.Name)) throw new ArgumentException("Stations.Pickup.Name required.");
        if (string.IsNullOrWhiteSpace(cfg.Stations.Dropoff.Name)) throw new ArgumentException("Stations.Dropoff.Name required.");
    }
}
