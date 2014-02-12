YACCoin has been successfully built from this package.

On linux, a Gentoo distribution was used.  Key packages installed were:

Boost 1.53.0
openssl 1.0.1f
db 4.8
miniupnpc 1.8 (required unless you specify "USE_UPNP=-" during builds

Under windows, the system was built natively using:

ActivePerl-5.15.3.1603-MWWin32-x6
Mingw-w64-v3.1.0
qt-win-opensource-4.8.5-mingw
boost_1_53_0
openssl-1.0.1f
db-4.8.30.NC
miniupnpc-1.8

The unix binaries and unix-QT image should build cleanly without any issues using the included makefiles.

Unix bbinary:

cd yaccoin/src
make clean -f makefile.unix
make -f makefile.unix

Unix-QT

cd yaccoin
qmake
make clean
make

Remember to uncomment the Windows and comment the single Unix line in yaccoin-qt.pro when building under Windows.

Windows "tricks":

1) As built, boost, openssl, db, and miniupnpc are stored in c:/deps in their own directories
2) The miniupnpc directory needs to have its number removed, just rename it.
3) For reasons that totally escape me, winsock2.h is not being pulled in by net.h as coded.  This results in rpcnet.ccp to die with a "ws2tpcip.h is not compatible with winsock.h.  Include winsock2.h instead" error message.  The only workaround I found was to go into the Ming32 directory and replace winsock.h with a copy of winsock2.h.  This is an incredibly ugly hack, but got it through the compile.
4) Anytime you change the .pro file, rerun qmake, make clean, and make.
5) If your desperate, check out this link.  I was, and it helped me a lot.
	https://bitcointalk.org/index.php?topic=149479.0
6) If you happen to use Avast! anti-virus, expect it to get a workout while you build and use the environment

Once all the tools are installed and built in your Windows environment, you should just be able to:

cd yaccoin
qmake yaccoin-qt.pro
make clean -f Makefile.Release
make -f Makefile.Release

7)  I had problems getting miniupnpc to build cleanly, so eventually punted and did:

qmake "USE_UPNP=-" yaccoin-qt.pro
make clean -f Makefile.Release
make -f Makefile.Release

