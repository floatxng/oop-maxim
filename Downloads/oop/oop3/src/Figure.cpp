#include "Figure.h"

std::ostream& operator<< (std::ostream& stream, const Figure& figure) {
    figure.print(stream);
    return stream;
}

std::istream& operator>> (std::istream& stream, Figure& figure) {
    figure.input(stream);
    return stream;
}
