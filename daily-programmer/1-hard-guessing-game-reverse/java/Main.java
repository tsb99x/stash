import java.util.Scanner;

class Main {

    public static void main(String[] args) {

        new Application().run();

    }

}

class Application {

    public void run() {

        final var scanner = new Scanner(System.in);

        var rangeMin = 0;
        var rangeMax = 100;

        System.out.println("You may pick a number in [0, 100]\n"
                + "Input [l] for lower, [h] for higher, [i] for it");

        for (var iter = 1;; iter++) {

            if (rangeMin == rangeMax) {
                System.out.println("Cheater! You re-picked number in the middle of game");
                return;
            }

            final var guess = (rangeMin + rangeMax) / 2;

            while (true) {

                System.out.print("Your number is '" + guess + "'? > ");

                var input = scanner.nextLine();
                if (input.equals("l")) {
                    rangeMax = guess;
                    break;
                }

                if (input.equals("h")) {
                    rangeMin = guess;
                    break;
                }

                if (input.equals("i")) {
                    System.out.println("PC won in '" + iter + "' iterations");
                    return;
                }

                System.out.println("Invalid input, please select one of [l], [h] or [i]");

            }

        }

    }

}