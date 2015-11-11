Vice 2.4.20 LIBRETRO WIP

Very WIP port of VICE 2.4.20 for libretro (using libco).
minimal Libretro arch port (no gui) 

 
Source base: 
http://sourceforge.net/p/vice-emu/code/HEAD/tree/tags/v2.4/v2.4.20/


VICE the Versatile Commodore Emulator

VICE is an emulator collection which emulates the C64, the C64-DTV, the C128, the VIC20, practically all PET models, the PLUS4 and the CBM-II (aka C610). It runs on Unix, MS-DOS, Win32, OS/2, Acorn RISC OS, BeOS, QNX 6.x, Amiga, GP2X or Mac OS X machines.


Developers

Current VICE team members: Dag Lem, Andreas Matthies, Martin Pottendorfer, Marco van den Heuvel, Christian Vogelgsang, Fabrizio Gennari, Daniel Kahlin, Antti S. Lankila, Groepaz, Ingo Korb, Errol Smith, Olaf Seibert, Marcus Sutton, Ulrich Schulz, Stefan Haubenthal, Thomas Giesel, Kajtar Zsolt, Benjamin 'BeRo' Rosseaux.

Of course our warm thanks go to everyone who has helped us in developing VICE during these past few years. For a more detailed list look in the documentation.

Copyright

The VICE is copyrighted to Andreas Boose, Tibor Biczo, Dag Lem, Andreas Dehmel, Andreas Matthies, Martin Pottendorfer, Spiro Trikaliotis, Marco van den Heuvel, Christian Vogelgsang, Fabrizio Gennari, M. Kiesel, Hannu Nuotio, Daniel Kahlin, Antti S. Lankila, Groepaz, Ingo Korb, Errol Smith, Olaf Seibert, Benjamin 'BeRo' Rosseaux, Markus Brenner, David Hansel, Thomas Bretz, Daniel Sladic, Ettore Perazzoli, André Fachat, Teemu Rantanen, Jouko Valta, Jarkko Sonninen.

VICE is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

VICE is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

--------------------------------------------------------------------------------------------------------------


Use it at you own risk !


Supported platforms : Linux Android

EMUTYPE is limited to : x64 (default) x64sc x64dtv x128

LIBDIR set to /mnt/srdcard/data for Android
and (retro_system_dir)/data for linux
 
Android Build:

make -f Makefile.libretro EMUTYPE=x64sc platform=android


