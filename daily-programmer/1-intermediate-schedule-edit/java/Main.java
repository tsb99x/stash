import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
import java.util.function.Consumer;

class Main {

    public static void main(String[] args) {

        new Application().run();

    }

}

class Application {

    private final static Scanner scanner = new Scanner(System.in);

    private final List<Event> events = new ArrayList<>();

    private final List<Command> commands = List.of(

            new Command("help", 0, args -> {

                System.out.println("command list: \n"
                        + "\t- help                 -- output current message    \n"
                        + "\t- list                 -- ordered list of all events\n"
                        + "\t- create {HOUR} {NAME} -- add new event             \n"
                        + "\t- update {INDEX}       -- edit specific event       \n"
                        + "\t- delete {INDEX}       -- remove specific event     \n"
                        + "\t- exit                 -- quit application          "
                );

            }),

            new Command("list", 0, args -> {

                if (events.isEmpty()) {
                    System.out.println("no events added yet");
                    return;
                }

                int idx = 0;
                for (final var event : events) {
                    System.out.println(idx + " : " + event);
                    idx++;
                }

            }),

            new Command("create", 2, args -> {

                try {

                    var hour = Integer.parseInt(args[1]);

                    if (hour < 0 || hour > 23) {
                        System.out.println("{HOUR} argument must be in [0, 23], but was '" + hour + "'");
                        return;
                    }

                    events.add(new Event(hour, args[2]));
                    events.sort(Comparator.comparingInt(Event::getHour));

                    System.out.println("event was successfully added");

                } catch (NumberFormatException e) {

                    System.out.println("{HOUR} argument must be an int");

                }

            }),

            new Command("update", 1, args -> {

                // copy of list's check
                if (events.isEmpty()) {
                    System.out.println("no events added yet");
                    return;
                }

                try {

                    var idx = Integer.parseInt(args[1]);
                    var event = events.get(idx);

                    try {

                        System.out.print("input {HOUR} (" + event.getHour() + ") > ");
                        var hourInput = scanner.nextLine();
                        if (!hourInput.isEmpty()) {
                            event.setHour(Integer.parseInt(hourInput));
                        }

                        System.out.print("input name (" + event.getName() + ") > ");
                        var nameInput = scanner.nextLine();
                        if (!nameInput.isEmpty()) {
                            event.setName(nameInput);
                        }

                        System.out.println("event was successfully updated");

                    } catch (NumberFormatException e) {

                        System.out.println("{HOUR} argument must be in [0, 23]");

                    }

                } catch (NumberFormatException e) {

                    System.out.println("{INDEX} argument must be an int");

                } catch (IndexOutOfBoundsException e) {

                    System.out.println("{INDEX} argument must be in [0, " + (events.size() - 1) + "]");

                }

            }),

            new Command("delete", 1, args -> {

                // copy of list's check
                if (events.isEmpty()) {
                    System.out.println("no events added yet");
                    return;
                }

                try {

                    var idx = Integer.valueOf(args[1]);
                    events.remove((int) idx);

                } catch (NumberFormatException e) {

                    System.out.println("{INDEX} argument must be an int");

                } catch (IndexOutOfBoundsException e) {

                    System.out.println("{INDEX} argument must be in [0, " + (events.size() - 1) + "]");

                }

            }),

            new Command("exit", 0, args -> {

                isRunning = false;

            })

    );

    private boolean isRunning = true;

    public void run() {

        while (isRunning) {

            System.out.print(" > ");
            final var input = scanner.nextLine();
            final var tokens = input.split(" ");

            commands.stream()
                    .filter(c -> c.getName().equals(tokens[0]))
                    .findFirst()
                    .ifPresentOrElse(c -> {

                        if (c.getArgCount() != tokens.length - 1) {
                            System.out.println("command '" + tokens[0] + "' requires '" + c.getArgCount() + "' arg(s)");
                            return;
                        }

                        c.getFunc().accept(tokens);

                    }, () -> {

                        System.out.println("failed to find command '" + tokens[0] + "'");

                    });

        }

    }

}

class Command {

    private final String name;
    private final int argCount;
    private final Consumer<String[]> func;

    public Command(String name, int argsCount, Consumer<String[]> func) {
        this.name = name;
        this.argCount = argsCount;
        this.func = func;
    }

    public String getName() {
        return name;
    }

    public int getArgCount() {
        return argCount;
    }

    public Consumer<String[]> getFunc() {
        return func;
    }

}

class Event {

    private int hour;
    private String name;

    public Event(int hour, String name) {
        this.hour = hour;
        this.name = name;
    }

    public int getHour() {
        return hour;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Event { "
                + "hour=" + hour + ", "
                + "name='" + name + "' "
                + "}";
    }

}