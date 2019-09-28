import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

import static java.nio.file.StandardOpenOption.APPEND;
import static java.nio.file.StandardOpenOption.CREATE;

class Main {

    public static void main(String[] args) throws IOException {

        new Application().run();

    }

}

class Application {

    public void run() throws IOException {

        var scanner = new Scanner(System.in);
        System.out.print("name > ");
        var name = scanner.nextLine();
        System.out.print("years > ");
        var years = scanner.nextLine();
        System.out.print("username > ");
        var username = scanner.nextLine();

        var result =
                "your name is '" + name + "', " +
                        "you are '" + years + "' years old, " +
                        "and your username is '" + username + "'";

        System.out.println(result);

        var logPath = Paths.get("log.txt");
        Files.writeString(logPath, result + '\n', CREATE, APPEND);

    }

}