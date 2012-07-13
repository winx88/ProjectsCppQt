#ifndef _MODES_H
#define	_MODES_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <math.h>
#include <cstdlib>

    double CosineTab[256];

    void initCosineTab() {
        for (int i = 0; i < 256; i++)
            CosineTab[i] = 64 - cos(i * M_PI / 255)*64;
    }

    int normalMode(int a, int b) {
        return b;
    }

    int averageMode(int a, int b) {
        return (a + b) / 2;
    }

    int multiplyMode(int a, int b) {
        return (a * b) >> 8;
    }

    int screenMode(int a, int b) {
        return 255 - ((255 - a) * (255 - b) >> 8);
    }

    int darkenMode(int a, int b) {
        if (a < b) {
            return a;
        } else {
            return b;
        }
    }

    int lightenMode(int a, int b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    }

    int differenceMode(int a, int b) {
        return abs(a - b);
    }

    int negationMode(int a, int b) {
        return 255 - abs(255 - a - b);
    }

    int exclusionMode(int a, int b) {
        return a + b - (a * b >> 7);
    }

    int overlayMode(int a, int b) {
        if (a < 128) {
            return (a * b) >> 7;
        } else {
            return 255 - ((255 - a) * (255 - b) >> 7);
        }
    }

    int hardlightMode(int a, int b) {
        if (b > 128) {
            return (a * b) >> 7;
        } else {
            return 255 - ((255 - b) * (255 - a) >> 7);
        }
    }

    int softlightMode(int a, int b) {
        int c = a * b >> 8;
        return c + a * (255 - ((255 - a)*(255 - b) >> 8) - c) >> 8;
    }

    int colordodgeMode(int a, int b) {
        if (b == 255)
            return 255;
        else {
            int c = (a << 8) / (255 - b);
            if (c > 255) return 255;
            else return c;
        }
    }

    int inversecolordodgeMode(int a, int b) {
        if (a == 255)
            return 255;
        else {
            int c = (b << 8) / (255 - a);
            if (c > 255) return 255;
            else return c;
        }
    }

    int softdodgeMode(int a, int b) {
        if (a + b < 256) {
            if (b == 255) {
                return 255;
            } else {
                int c = (a << 7) / (255 - b);
                if (c > 255) return 255;
                else return c;
            }
        } else {
            // a cannot be zero here
            int c = 255 - (((255 - b) << 7) / a);
            if (c < 0) return 0;
            else return c;
        }
    }

    int colorburnMode(int a, int b) {
        if (b == 0)
            return 0;
        else {
            int c = 255 - (((255 - a) << 8) / b);
            if (c < 0) return 0;
            else return c;
        }
    }

    int inversecolorburnMode(int a, int b) {
        if (a == 0)
            return 0;
        else {
            int c = 255 - (((255 - b) << 8) / a);
            if (c < 0) return 0;
            else return c;
        }
    }

    int softburnMode(int a, int b) {
        if (a + b < 256) {
            if (a == 255) {
                return 255;
            } else {
                int c = (b << 7) / (255 - a);
                if (c > 255) return 255;
                else return c;
            }

        } else {
            // b cannot be zero here
            int c = 255 - (((255 - a) << 7) / b);
            if (c < 0) return 0;
            else return c;
        }
    }

    int reflectMode(int a, int b) {
        if (b == 255) {
            return 255;
        } else {
            int c = a * a / (255 - b);
            if (c > 255) return 255;
            else return c;
        }
    }

    int glowMode(int a, int b) {
        if (a == 255)
            return 255;
        else {
            int c = b * b / (255 - a);
            if (c > 255) return 255;
            else return c;
        }
    }

    int freezeMode(int a, int b) {
        if (b == 0)
            return 0;
        else {
            int c = 255 - (255 - a)*(255 - a) / b;
            if (c < 0) return 0;
            else return c;
        }
    }

    int heatMode(int a, int b) {
        if (a == 0)
            return 0;
        else {
            int c = 255 - (255 - b)*(255 - b) / a;
            if (c < 0) return 0;
            else return c;
        }
    }

    int additiveMode(int a, int b) {
        int c = a + b;
        if (c > 255) return 255;
        else return c;
    }

    int subtractiveMode(int a, int b) {
        int c = a + b - 256;
        if (c < 0) return 0;
        else return c;
    }

    int stampMode(int a, int b) {
        int c = a + 2 * b - 256;
        if (c < 0)
            return 0;
        else if (c > 255)
            return 255;
        else
            return c;
    }

    int interpolationMode(int a, int b) {
        int c = CosineTab[b] + CosineTab[a];
        if (c > 255) return 255;
        else
            return c;
    }

    int logicalXORMode(int a, int b) {
        return a ^ b;
    }

    int logicalORMode(int a, int b) {
        return a & b;
    }

    int logicalANDMode(int a, int b) {
        return a | b;
    }
#ifdef	__cplusplus
}
#endif

#endif	/* _MODES_H */

