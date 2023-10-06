This is first lab of the cource OOP on CPP.

To see directory structure, type:
```bash
$ tree Lab1/
```

To build project with test, type following:

```bash
$ mkdir build && cd build
$ cmake ../
$ make
```

And without tests:

```bash
$ mkdir build && cd build
$ cmake -DLAB1_TESTING=OFF ../
$ make
```