# SnakeHead

So I decided to make an interesting game Snake - yes, i mean, the typical one, the "Snake", but then, there were a few problems that the snake's tails did't move, so here i'm introducing, the total new version of Snake : SNAKE-HEAD. Enjoy it, tadaaaa :>

## Reference Source

* [Lazy Foo' Tutorials](http://lazyfoo.net/tutorials/SDL/index.php) - Collision Dectection, Init the game's basic form
* [phattrienphanmem123az](https://phattrienphanmem123az.com/lap-trinh-game-c-p2) - The Main Source as checking map, separating class code, clipping spritesheets, ...
* [How To Make A Game In C++ & SDL2 From Scratch!](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx) - A Tutorial from Let's Make Game, implementing on main.cpp


## Getting Started

This is a really simple game to play!

- press any key to start
- using your arrow keys, 
- control a snake, 
- try to collect coin and strawberry, 
- avoid touching border and enemies
- press r to replay

### Prerequisites
SDL version 2.0.12 including:

```
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf
```

### Installing

Contact me to get the zip file, so all you need to do is extracting file, finding the .exe and start enjoying your game :D

## Running the tests

Check my youtube channel for the demo of the game: https://www.youtube.com/watch?v=BpjX6KBRW_c

## Features, Coding Style and Deployment

- A menu start and a menu end
- Replay by pressing r
- Different music in the end
- Effect sound: collect coin, touch enemies
- Enemies choose random directions ()
- Count point
- Different spritesheets for different directions (left, right)
- main.cpp is easy to follow (init -> loadMedia -> (game-loop(handleEvent->update->render)) -> end)
- Implementing inheritance, virtual function ()
- Seperated files for different purposes
- Utils.h storing: (preprocessor directive), (basic properties of the game (which are constant values)) and (functions that commonly used)
- (Resource File) storing resources in game (media, map, font)
- Implementing lessons learnt: reading files (using fstream), using pointers (in order to save memory, optimize proj), using class, ...

## Built With

* [SDL2](https://wiki.libsdl.org/) - The  cross-platform development library used
* [C++](https://en.wikipedia.org/wiki/C%2B%2B) - Language used

## Authors

* **Anh Nguyet Duong** - *Initial work* - [Freelancer](https://github.com/duonanh195)

## License

Open source

## Acknowledgments

* Updating optimization
* Updating the high score
* Not really creative
