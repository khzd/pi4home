from __future__ import print_function
import sys


def main():
    print("The pi4homeyaml command has been renamed to pi4home.")
    print("")
    print("$ pi4home {}".format(' '.join(sys.argv[1:])))
    return 1


if __name__ == "__main__":
    sys.exit(main())
