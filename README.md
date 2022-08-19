# Conways-Game-of-Life-War-Edition
This is a fun little project I decided to work on to learn how to use Raylib's library. In this game(although it's more of a simulation than a game), you have an empty board where cells can spawn in via "reproduction" or die off as from "overpopulation.
Here is the wikipedia link: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
\
\
The basic rules of Conways Game of Life are:
1. Any live cell with two or three live neighbours survives.
2. Any dead cell with three live neighbours becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

That's how the regular "game" works, and there are a ton of resources where you can see it in action if you're curious! In my twist, also known as "War Edition", adds in another seperate group of cells that interact with eachother.\
\
Here's an example:

![Example 1 Gif](https://user-images.githubusercontent.com/111163384/185544739-71635fb8-2a15-4050-a1c1-0260bc44c579.gif)

As you can see, these two cell groups don't merge at all! So here are the rules of War Edition that I created:
- Any dead cell can still spawn with three live neighbors, but "enemy" cells do not count.
- Any live cell with surrounded by more "enemies" than "allies" will die, regardless of friendly neighbors.

Here are other fun gifs of the simulation!\
![Exampe 2](https://user-images.githubusercontent.com/111163384/185546711-aea5f25e-9d35-4527-a22e-dd4f6cc45bee.gif)

![Example 3](https://user-images.githubusercontent.com/111163384/185547413-6b15ffcd-7d16-458e-b8cc-509a5cb9d7b8.gif)

![Example 4](https://user-images.githubusercontent.com/111163384/185547582-f9a7f172-b824-412a-913a-9703128fc79e.gif)

It's a lot of fun to play around with it. Here's a short clip of the introduction of the program and as well as the layout of how it looks when using it.

![Intro Vid](https://user-images.githubusercontent.com/111163384/185553411-f76d7a0f-de97-483a-8daf-64212918bc54.gif)

You can also delete cells during paused simulation if you want to manually remove some cells. As you can see, it also shows the sizes of the two different groups of cells, and lets you know if the simulation is running or paused.


