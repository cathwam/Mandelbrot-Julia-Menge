// Aufgabe 1
// Loris Wilwert, Raphael Julien Ebner, Catherine Wampach

#include "point.hh"
#include "canvas.hh"
#include <iostream>
#include <cmath>
#include <string>

/* ----- Punkt a) -----*/
class IterationResult {
    private:
        Point _p;
        int _num_of_it;
    
    public:
        // constructor
        IterationResult(Point p0) : _p(p0), _num_of_it(0) {}

        // getters
        Point p() const {
            return _p;
        }

        int numOfIt() const {
            return _num_of_it;
        }

        // setters
        void setP(double x, double y) {
            _p = Point(x, y);
        }

        void setNumOfIt(int i) {
            _num_of_it = i;
        }

        // Gebe die Norm von _p zurück
        double norm() const {
            return std::sqrt( std::pow(this->p().x(), 2) + std::pow(this->p().y(), 2));
        }
};


/* ----- Punkt b) ----- */
IterationResult iterate (Point z, Point c, double threshold, int maxIt) {
    IterationResult it(z);

    for (int i = 1; i <= maxIt; ++i) {
        it.setP( std::pow(it.p().x(), 2) - std::pow(it.p().y(), 2) + c.x(), 2 * it.p().x() * it.p().y() + c.y() );
        it.setNumOfIt(it.numOfIt() + 1);

        if (it.norm() > threshold) 
            return it;
    }
    return it;
}


/* ----- Punkt c) ----- */
void mandelbrot(Canvas& canvas, double threshold, int maxIt, std::string filename, bool smooth = false) {
    int i, j;
    for (i = 0; i < canvas.horPixels(); ++i) {
        for (j = 0; j < canvas.vertPixels(); ++j) {
            IterationResult it = iterate(Point(), canvas.coord(i, j), threshold, maxIt);
            if (it.numOfIt() == maxIt)
                canvas(i, j) = 0;
            else 
                if (smooth)
                    /* ----- Aufgabe 3 ----- */
                    canvas(i, j) = std::log( it.numOfIt() - std::log2( std::log(it.norm()) / std::log(threshold) ) ) * 100;
                else
                    canvas(i, j) = std::log( it.numOfIt() ) * 100;
        }
        // Gebe die Prozentangabe der bereits erstellten Fläche in der Konsole zurück
        if ((i + 1) % (canvas.horPixels()/10) == 0) 
            std::cout << 10 * (i + 1) / (canvas.horPixels()/10) << "% erstellt" << std::endl << std::flush; 
    }
    std::cout << "schreibe in " << filename << std::endl;
    canvas.write(filename);
}


int main() {
    Point center = Point(-1, 0);
    // Wenn wir eine etwas größere Breite und Höhe wählen, dann sind weniger Pixel in der Mandelbrot Menge (also schwarz) 
    // und damit sinkt die Berechnungszeit
    const double width = 8, height = 8;
    const int horPixels = 4000, vertPixels = 3000, maxIt = 500, threshold = 100;
    const bool smooth = true;

    // Die Dunkelheit des Bildes wächst mit maxIt
    // Die etwas helleren ovalen "Kreise" um die Mandelbrot Menge herum wachsen mit threshold

    Canvas canvas(center, width, height, horPixels, vertPixels);

    mandelbrot(canvas, threshold, maxIt, "mandelbrot.pgm", smooth);

    return 0;
}
