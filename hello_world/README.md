# Hello World - XCompiler Test
 
SSHFS Verbindung aufbauen
    sshfs pi@192.168.0.90:/home/pi/bin "`pwd`/bin"
    
## Password-Verwaltung
Kennwort ist im File `.config/passwords.cmake` abgelegt  
Aus Sicherheitsgründen kann dass PW auch als Environment-Variable gespeichert werden

Um zu Verhindern dass das Kennwort auf GH zu finden ist wird folgende Strategie
verwendet:

   - File wird mit "dummy-Password" erstellt  
   (Beim Generieren durch CMake wird das File `src/config.h` erstellt)
    
   - Check in der beiden Files (`passwords.cmake + config.h`)

   - Hinzufügen der Files zu `.gitignore`:  
   (Nicht sicher ob das wirklich notwendig ist!)
   
    .config/passwords.cmake
    src/config.h
   
### Aktivieren + De-Aktivieren von getrackten Files    

    # De-Aktivieren
    git update-index --assume-unchanged .config/passwords.cmake
    git update-index --assume-unchanged src/config.h

    # Aktivieren (sollte selten der Fall sein!)
    git update-index --no-assume-unchanged .config/passwords.cmake
    
    # Aktivieren von src/config.h - Fraglich ob das überhaupt irgendwann notwendig ist!
    git update-index --no-assume-unchanged src/config.h

#### Betreffende files online:

   - [passwords.cmake](https://github.com/MikeMitterer/cpp-xctest/blob/master/hello_world/.config/passwords.cmake)
   - [config.h](https://github.com/MikeMitterer/cpp-xctest/blob/master/hello_world/src/config.h)
   
   