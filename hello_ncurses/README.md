## Hello NCurses - XCompiler Test
 
SSHFS Verbindung aufbauen
    sshfs pi@192.168.0.90:/home/pi/bin "`pwd`/bin"
    
### gcc 4.9.3 cross-compiler (Mac)
Filesystem changes (PIROOT)/usr/lib/arm-linux-gnueabihf:

   - libc.so       
   - libncurses.so
   - libpthread.so
   
These .so-Files are TEXT-Files (not symlinks!)

Path in these files had to be prefixed with (PIROOT). In my case
   
    /Volumes/DataElCapitan/raspberry/rpi1/rootfs
    
Sample - libc.so  
Original:

    /* GNU ld script
       Use the shared library, but some functions are only in
       the static library, so try that secondarily.  */
    OUTPUT_FORMAT(elf32-littlearm)
    GROUP ( /lib/arm-linux-gnueabihf/libc.so.6 /usr/lib/arm-linux-gnueabihf/libc_nonshared.a  AS_NEEDED ( /lib/arm-linux-gnueabihf/ld-linux-armhf.so.3 ) )

Prefixed:  

    /* GNU ld script
       Use the shared library, but some functions are only in
       the static library, so try that secondarily.  */
    OUTPUT_FORMAT(elf32-littlearm)
    GROUP ( /Volumes/DataElCapitan/raspberry/rpi1/rootfs/lib/arm-linux-gnueabihf/libc.so.6 /Volumes/DataElCapitan/raspberry/rpi1/rootfs/usr/lib/arm-linux-gnueabihf/libc_nonshared.a  AS_NEEDED ( /Volumes/DataElCapitan/raspberry/rpi1/rootfs/lib/arm-linux-gnueabihf/ld-linux-armhf.so.3 ) )

More Infos on [SO](http://stackoverflow.com/a/7487951/504184)
and on [raspberrypi.org](https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=37658)

Moved according .so files to MODS-Folder

    # In /Volumes/DataElCapitan/raspberry/rpi1/rootfs/usr/lib/arm-linux-gnueabihf
    
    $ cp libc.so ../../../../mods/
    $ cp libncurses.so ../../../../mods/
    $ cp libpthread.so ../../../../mods/
    
### Additional CMakeLists-Settings

    target_link_libraries(
            ${PROJECT_NAME}
            menu
            ${curses_LIBRARY}
    
            # Solves: undefined reference to symbol 'curs_set'
            # More: https://goo.gl/9dtJsO
            tinfo
    )


