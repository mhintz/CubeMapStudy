.PHONY: build run

all: build run

build:
	xcodebuild -configuration Debug -project xcode/CubeMapStudy.xcodeproj/

run:
	./xcode/build/Debug/CubeMapStudy.app/Contents/MacOS/CubeMapStudy
