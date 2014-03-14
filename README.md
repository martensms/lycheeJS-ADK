
# lycheeJS-ADK (v0.5 pre-release)

Web Documentation: [http://martens.ms/lycheeJS](http://martens.ms/lycheeJS)

The lycheeJS-ADK (App Development Kit) is the advanced build
toolchain and environment for the [lycheeJS Game library](https://github.com/martensms/lycheeJS).

It also includes a custom V8-based JIT runtime with OpenGL, GLU
and GLUT integration and custom data types for interaction and
allows cross-compiling your JavaScript Games to different
platforms via native executables or packages.


# License

The lycheeJS-ADK is released under MIT license.


# Development Environment

The recommended development environment is [Ubuntu 12.10 64Bit](http://ubuntu.com/download)
with an underlying machine setup:

- CPU supports either the complete amd64 or the intel64 (IA-32e, EM64T) instruction set.
- GPU **and** installed driver supports OpenGL 2.1 (at least OpenGL 2.0).


**How to verify the correct OpenGL version:**

The installed OpenGL version should be higher than 2.1. You can verify the OpenGL version
string of your graphics card by executing the following line in your shell:

```bash
$ glxinfo | grep "OpenGL version"

OpenGL version string: 4.2.11627 Compatibility Profile Context
```


# Getting Started


## Step 1: Download

You first need to download and install the required lycheeJS-ADK files,
therefore you can choose of two methods:

**Method 1: Cloning the git repository**

```bash
git clone git://github.com/martensms/lycheeJS-adk.git ~/Desktop/lycheeJS-adk;
```

**Method 2: Downloading via zip file**

[Download the zip file](https://github.com/martensms/lycheeJS-adk/archive/master.zip)
and unpack the contents inside the zip files' root folder it to your *~/Desktop/lycheeJS-adk* folder.

(So that the setup.sh script is located at *~/Desktop/lycheeJS-adk/setup.sh*)


## Step 2: Setup

After you have plain installation of the lycheeJS ADK, you need to
setup your environment and install the dependend libararies, development
headers and such. The setup script will also build the ADK itself (which
is in fact a V8GL runtime for your machine's architecture).

```bash
cd ~/Desktop/lycheeJS-adk;
chmod +x ./setup.sh; # In case you downloaded the zip file
./setup.sh;
```


## Step 3: Game Engine-specific Bootstrapping


```bash
cd ~/Desktop/lycheeJS-adk;
./adk bootstrap --adapter=lycheeJS
```


## Step 3: Your first native build

You can now start creating native builds.

The build process itself requires a few minutes at the first time, due to
building all required V8 libraries and snapshots.

A simple start point of learning how to develop games with lycheeJS is
to try out the code of the Boilerplate or the Jewelz Game.

```bash
cd ~/Desktop/lycheeJS-adk;
./adk build linux.x64 ./external/lycheeJS/game/jewelz --adapter=lycheeJS

# Testing
cd ./out/Linux.x64;
./v8gl;
```

For a 32 Bit system, you should build *linux.ia32* instead.

