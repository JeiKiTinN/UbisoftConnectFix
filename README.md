# UbisoftConnectFIX
 UbisoftConnectFIX aims to fix performance issues that occur when using Ubisoft Connect.
 
I am not a representative of Ubisoft, if I violate any of your law, please contact me, I will try to remedy the situation. Excuse also my English.

What's the problem?
====
I ran into a problem when playing Far Cry 6. Every time I open an overlay of Ubisoft Connect my FPS tends to 10-15.
I also found a problem on the [reddit - contrabardus](https://www.reddit.com/r/farcry/comments/q32753/heads_up_disabling_the_ubiconnect_overlay/?utm_source=share&utm_medium=web2x&context=3).

The main method is to disable the Ubisoft Connect overlay and then start the game. The thing is, I wanted to play with a friend, and when I turned off the overlay, the services of ubisoft stopped working. So I needed a way to keep the overlay, but reduce the load.

Reading the comments I found a man with a nickname - Yehorka18. His method is the basis of my program.

What does the program do?
====
Finds Ubisoft Connect processes and does with them:
1. Lowers priority
2. Leaves one core for the process

Ubisoft Connect overlay can hang/lag it all because of program manipulation.

How do I run this? I don’t have programming skills!
====

You can download the source code and compile yourself or download the latest version here.

You’ll need to unpack the program from the archive. Then launch Far Cry 6 (or any other game in Ubisoft Connect) and after you are in the menu, run the program (.exe file). You should see something like [this](https://prnt.sc/KO1aWkp3pBEt). If you see 11, it means that the program works correctly. After that, press Enter and the program will close automatically.

Enjoy.

It doesn’t work on my computer! What to do?
====
Contact me and provide the information you need. If the program has given you a specific problem or you have suggestions for improvement, comments, you can also contact me, I am happy to help.

Please note that the performance is not guaranteed. Testing was done on Windows 10 - 21H2. 

I tested the program on Virus Total and found viruses!
====
Then refrain from using the program.

Before:
![Before](https://user-images.githubusercontent.com/44775752/179285287-419ee9c1-0952-4788-a4bc-af50260391ce.PNG)

After:
![After](https://user-images.githubusercontent.com/44775752/179285501-9c349f57-714e-4b14-9432-0b1c4f2d25e1.PNG)
