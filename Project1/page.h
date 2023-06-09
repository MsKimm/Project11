#include <vector>
#include <algorithm>

class Page {
public:
    std::vector<int> above;
    int getX() { return x; }
    int getY() { return y; }
    int getW() { return width; }
    int getH() { return height; }
    int getid() { return id; }
    char getcont() { return content; }
    
    Page(int x, int y, int width, int height, int id, int content)
        : x(x), y(y), width(width), height(height), id(id), content(content) {}
    int x, y; // position of the page on the board
    int width, height; // width and height of the page 
    int id; // unique id for each page
    char content;


private:


};