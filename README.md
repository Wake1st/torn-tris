# Game Design Patterns

Design pattern implementations from the book [Game Programming Patterns](https://gameprogrammingpatterns.com/contents.html) using the [raylib](https://github.com/raysan5/raylib) library.

## Instructions

Follow these instructions to run the program locally.

1. Clone repo.
  ```
  git clone https://github.com/Wake1st/GameDesignPatterns.git
  ```
2. Step into directory.
  ```
  cd GameDesignPatterns
  ```
3. Build program.
  ```
  make all
  ```
4. Run program.
  ```
  bin/program
  ```

Select the level type from the main menu and follow the instructions provided.

## Patterns

I did my best to implement a few design patterns from the book. Some are more custom, diverging from the book's examples, but I did my best to adhere the core principles.

### [Command](https://gameprogrammingpatterns.com/command.html)

Simple and straightforward, I figured the command pattern was a must for a portfolio project.

### [Event Queue](https://gameprogrammingpatterns.com/event-queue.html)

So, technically, this isn't an event queue - not like the book, at least. Instead, this implementation is different from the book in two ways:
- instead of sound, the `InputQueue` takes movement inputs, and
- instead of processing the queue in the one frame, the `InputQueue` runs commands sequentially based on a timer.

The real usefullness of this implementation is having a "looping" array (the tail, and eventually the head, loops back to be begining of the array). While there are different data structures which probably offer the same functionality, I like the simplicity of two moving indices along a fixed array. 

## Known Issues

- `InputQueue` display sometimes shows right facing arrows for left movement.

## Resources

- [Game Programming Patterns](https://gameprogrammingpatterns.com/contents.html)
- [raylib](https://github.com/raysan5/raylib)
