from distutils.core import setup, Extension

extension = Extension(
    name='aclib_injector',
    sources=[
        'source/python/ACLIBInjector.cpp',
        'source/python/PyDLLInject.cpp',
        'source/DLLInject.cpp',
    ],
    include_dirs=['source/', '../Common/include'],
    library_dirs=[],
    libraries=[],
    extra_compile_args=['/Ot'])


setup(name='aclib_injector',
      version='1.0',
      ext_modules=[extension],
      libraries=[])
