from setuptools import setup, find_packages

setup(
    name="nanoai",
    version="1.0.0",
    packages=find_packages(),
    author="NanoAI Team",
    description="Universal offline AI runtime SDK",
    long_description=open("../../README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/abdulraheemnohri/NanoAI-Runtime-SDK",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.6",
)
