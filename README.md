# SnakeHead

So I decided to make an interesting game Snake - yes, i mean, the typical one, the "Snake", but then, there were a few problems that the snake's tails did't move, so here i'm introducing, the total new version of Snake : SNAKE-HEAD. Enjoy it, tadaaaa :>

## **UPDATE** <Since 05/2020>
__1. New README__ 

__2. New comment:__ 

  * ![cmt1](https://user-images.githubusercontent.com/41201391/82917002-01606d80-9f9d-11ea-8df7-2e042d9f29b3.JPG)
  * ![cmt2](https://user-images.githubusercontent.com/41201391/82917139-366cc000-9f9d-11ea-90e2-9f209051b0c0.JPG)
  * ![cmt3](https://user-images.githubusercontent.com/41201391/82917148-3967b080-9f9d-11ea-9fde-920c32fcf673.JPG)

__3. New ending background (Press ~~any key~~ to restart -> Press _r_ to restart):__ 

  * Before: ![OldendBackground](https://user-images.githubusercontent.com/41201391/82917764-096cdd00-9f9e-11ea-8adb-49b7d1367f7d.png)
  * After: ![endBackground](https://user-images.githubusercontent.com/41201391/82917789-11c51800-9f9e-11ea-8081-69b508924c08.png)
  
__4. Replay: Press r to change status from endBackground(2) to startBackground(0)__ 

  * ![replay](https://user-images.githubusercontent.com/41201391/82917982-4c2eb500-9f9e-11ea-8e2f-2871c17b0ba2.JPG)
  
__5. Change loadImage function of PlayerObject:__ 

  * ![loadImage](https://user-images.githubusercontent.com/41201391/82918263-a891d480-9f9e-11ea-9fd0-e09086d0e439.JPG)
  
__6. free ThreatObjects used (the game object that inherits from BaseObject) :__

  * ![freeThreatObject](https://user-images.githubusercontent.com/41201391/82918407-decf5400-9f9e-11ea-8690-ce35d61c8b8d.JPG)
  


## Reference Source

* [Lazy Foo' Tutorials](http://lazyfoo.net/tutorials/SDL/index.php) - Collision Dectection, Init the game's basic form
* [phattrienphanmem123az](https://phattrienphanmem123az.com/lap-trinh-game-c-p2) - The Main Source as checking map, separating class code, clipping spritesheets, ...
* [How To Make A Game In C++ & SDL2 From Scratch!](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx) - A Tutorial from Let's Make Game, implementing on main.cpp

## Features, Coding Style and Deployment

- A ***menu start*** and a ***menu end***
- Press any key to start. ***Replay*** by pressing r
- Different ***music in the end***
- ***Effect sound***: collect coin, touch enemies
- Enemies choose ***random directions*** ()
- Count ***point***
- Different spritesheets for different directions (left, right)
- main.cpp is easy to follow ***(init -> loadMedia -> (game-loop(handleEvent->update->render)) -> end)***
- Implementing inheritance, virtual function ()
- ***Seperated files*** for different purposes
- Utils.h storing: (***preprocessor directive***), (***basic properties of the game*** (which are constant values)) and (***functions that commonly used***)
- (***Resource File***) storing resources in game (media, map, font)
- Implementing lessons learnt: reading files (using ***fstream***), using ***pointers*** (in order to save memory, optimize proj), using ***class***, ...

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

## Built With

* [SDL2](https://wiki.libsdl.org/) - The  cross-platform development library used
* [C++](https://en.wikipedia.org/wiki/C%2B%2B) - Language used

## Authors

* [**Anh Nguyet Duong**](https://github.com/duonanh195)

## License

Open source

## Acknowledgments

* Updating optimization
* Updating the high score
* Not really creative
