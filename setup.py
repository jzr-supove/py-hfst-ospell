#!/usr/bin/env python
# -*- coding:utf-8 -*-

"""Setup this SWIG library."""
import runpy

from setuptools import Extension, find_packages, setup
from setuptools.command.build_py import build_py


STD_EXT = Extension(
    name='_py_hfst_ospell',
    swig_opts=['-c++'],
    sources=[
        'src/py_hfst_ospell/py-hfst-ospell.cpp',
        'src/py_hfst_ospell/py-hfst-ospell.i',
        "src/py_hfst_ospell/hfst-ol.cc",
        "src/py_hfst_ospell/ospell.cc",
        "src/py_hfst_ospell/ZHfstOspeller.cc",
        "src/py_hfst_ospell/ZHfstOspellerXmlMetadata.cc"
    ],
    include_dirs=[
        'src/py_hfst_ospell',
    ],
    extra_compile_args=[  # The g++ (4.8) in Travis needs this
        '-std=c++11',
    ]
)


# Build extensions before python modules,
# or the generated SWIG python files will be missing.
class BuildPy(build_py):
    def run(self):
        self.run_command('build_ext')
        super(build_py, self).run()


INFO = runpy.run_path('src/py_hfst_ospell/_meta.py')

setup(
    name='py-hfst-ospell',
    description='A Python wrapper for HFST Ospell',
    version=INFO['__version__'],
    author=INFO['__author__'],
    license=INFO['__copyright__'],
    author_email=INFO['__email__'],
    url=INFO['__url__'],
    keywords=['SWIG', 'ospell'],

    packages=find_packages('src'),
    package_dir={'': 'src'},
    package_data={'': ['*.pyd']},
    ext_modules=[STD_EXT],
    cmdclass={
        'build_py': BuildPy,
    },

    python_requires='>=3.7'
)
