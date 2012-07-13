#ifndef _MYIMAGE_H
#define	_MYIMAGE_H
#include<vector>
#include<QImage>
#define DL 500
using namespace std;

class myImage : public QImage {
public:
    myImage(int, int, QImage::Format);
    void change(int &, int &);
    void clean();
    void line(int, int, int, int);
};

#endif	/* _MYIMAGE_H */

