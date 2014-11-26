MuOnline
========

MuOnline

Step 1, install all .NET Frameworks. (including client profiles) and Microsoft Visual C++ 2010 Redistributable Package (x86) and (x64)

Step 2, install DirectX End-User Runtimes (June 2010)


Step 3, install mysql workbech (need Visual C++ Redistributable)


Step 4, download dependencies, boost and media.


Dependencies: https://mega.co.nz/#!1ZtA0CoI!LNOiJ15_NZSXdnvxKNEO5foJc5gVxF9Emj_qvAYVH8I


Boost: https://mega.co.nz/#!ZBdBgaTY!FfnIzy2ZK4kH1ER3xBQY2vHGcjG5efJ3hnVQ8DheLJ4


Media: https://mega.co.nz/#!cZ8SRKDR!UZ29pvQKiv31vmnVkaMyIehuLbbAQ6IBOYi2JVr9PA8


step 5, extract dep, boost and media in MuOnline folder.


Step 6, open mysql workbench, open connection, go to Server->Data Import, and select muonline.sql (located in DataBase folder, Dirac server, this should restore the db, pretty empty but dirac needs it!.)


Step 7, Open Dirac solution (v 10 or 13), build it, open config.ini, in the [DataBaseConfig] section, write your user and password 


Step 8, Open MU.sln, select release config, second click in the solution, REBUILD ALL.


Step 9, Now, run dirac server (debug or release, whatever) and then, from the VS instance, run the MegaProjectNative app and you are done ;)
