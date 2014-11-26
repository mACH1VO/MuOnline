MuOnline
========

MuOnline

Step 1, install all .NET Frameworks. (including client profiles) and Microsoft Visual C++ 2010 Redistributable Package (x86) and (x64)

Step 2, install DirectX End-User Runtimes (June 2010)


Step 3, install mysql workbech (Visual C++ Redistributable 2013 and .NET 4 client profile needed, according to oracle)


Step 4, download dependencies, boost and media.


Dependencies: https://mega.co.nz/#!1ZtA0CoI!LNOiJ15_NZSXdnvxKNEO5foJc5gVxF9Emj_qvAYVH8I


Boost: https://mega.co.nz/#!ZBdBgaTY!FfnIzy2ZK4kH1ER3xBQY2vHGcjG5efJ3hnVQ8DheLJ4


Media: https://mega.co.nz/#!cZ8SRKDR!UZ29pvQKiv31vmnVkaMyIehuLbbAQ6IBOYi2JVr9PA8


Step 5, extract dep, boost and media in MuOnline folder. (uncompressed boost is about 3gb)


Step 6, open mysql workbench, open root connection, go to Server->Data Import, and select muonline.sql (located in DataBase folder, Dirac server, this should restore the db, it's quite empty but dirac needs it!.)


Step 7, open Dirac solution (v 10 or 12/13), build it, open config.ini, in the [DataBaseConfig] section, write your user and password 


Step 8, Open MU.sln, select release config, second click in the solution, REBUILD ALL. (could take hours).
note: you can build also the debug version, but the framerate will be very low.
note2: th default option when rebuilding the solution is to create the precompiler headers, to change that, select "Use precompiler headers" and build again.


Step 9, Now, run dirac server (debug or release, whatever) and then, from the VS instance, run the MegaProjectNative app and you are done ;)
