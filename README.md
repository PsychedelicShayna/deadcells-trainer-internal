# Dead Cells Internal Trainer

This is an old internal hack I wrote for Dead Cells a long time ago that likely doesn't work anymore and was built for Windows, which I don't use anymore. Still I think this repository serves some educational value to those looking to do the same. I kept some of my notes, article links, and other stuff that I used when making it.

Feel free to reverse engineer the code, that's the whole point of me publishing this! Seriously, there's a 80% chance this won't even work anymore, this was from 2022, the game's layout must have certainly changed since then.. then again who knows maybe it still works, I don't have a Windows environment to try.

To be clear, when I say internal hack, that means that everything is achieved from within the game's memory via DLL injection and trampoline hooking DX11 so this isn't an external "just touch the game's memory with a stick" trainer, this is intended to be used with a DLL injector (I used Process Hacker at the time for this, but any old DLL injector will work).


I did use QMake as my build system for this project (sorry), but it's relatively easy to read the `.pro` file and figure out how to build it if you actually want to build this DLL yourself for some reason (it really isn't likely to work)

I forgot __everything__ it could do, but it used an ImGUI overlay and definitely did support the following 

- Max Health
- Setting Health 
- Setting Gold
- Setting Cells
- Setting Flasks
- Unlimited Flask Charges
- Noclip / Flyhack
- Unlimited Jump Hack
- Prolly More I don't remember

I found an old screenshot of when not all of those features were implemented yet, but at some point the overlay looked like this in early phases of development:

I hope this helps anyone curious about game hacking on Windows. I've since moved onto Linux, and might repeat the whole thing again but on Linux!
