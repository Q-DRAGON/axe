"""
1. Set environment variable C_INCLUDE_PATH to include the directory of your python distribution.

Example: 1. Get include directory of your python distribution

    find /usr/local/Cellar/ -name Python.h

This will return something like this:

    /usr/local/Cellar//python3/3.6.3/Frameworks/Python.framework/Versions/3.6/include/python3.6m/Python.h

Now Set you C_INCLUDE_PATH variable:

    export C_INCLUDE_PATH="/usr/local/Cellar//python3/3.6.3/Frameworks/Python.framework/Versions/3.6/include/python3.6m/"

This MAC:

    export C_INCLUDE_PATH="/usr/local/Cellar//python3/3.6.4/Frameworks/Python.framework/Versions/3.6/include/python3.6m/"

2. official texture - 1.6:
    https://docs.python.org/3.6/extending/embedding.html

3. pythonX.Y-config --cflags will give you the recommended flags when compiling:

    $ /opt/bin/python3.4-config --cflags

This MAC 编译:

    cc main.c -L/usr/local/opt/python3/Frameworks/Python.framework/Versions/3.6/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation

This MAC 运行：

    cc main.c -L/usr/local/opt/python3/Frameworks/Python.framework/Versions/3.6/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation && ./a.out

"""
