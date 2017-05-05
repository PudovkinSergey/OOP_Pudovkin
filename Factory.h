#include "Shapes.h"
#include <ctime>
#include <random>
enum shape { POINT, CIRCLE, RECT, SQUARE, POLYLINE, POLYGON };

std::mt19937 gen ( (int)time(0) ); 
std::uniform_real_distribution <> randreal( -1000,1000 );
std::uniform_int_distribution <> randint( 1,50 );

Point Newpoint()
{
	Point newpoint( "Point(" + ToString( randint(gen) ) + ") ", randreal(gen), randreal(gen) );
	return newpoint;
}

Shape figure( int type ) {
	Shape shape;
	switch ( type ) {

		case POINT: {
			shape = Newpoint();
			break;
		}

		case CIRCLE: {
			Point  center = Newpoint();
			Circle newcircle( "Circle(" + ToString( randint(gen) ) + ")", center, randreal(gen));
			shape = newcircle;
			break;
		}

		case RECT: {
			Point p1 = Newpoint();
			Point p2( "Point(" + ToString( randint(gen) )+")", p1.GetX() + abs( randreal(gen) ), p1.GetY() - abs( randreal(gen) ));
			Rect newrect( "Rect(" + ToString( randint(gen) ) + ")", p1, p2 );
			shape = newrect;
			break;
		}

		case SQUARE: {
			Point p1 = Newpoint();
			double slide = abs( randreal(gen) );
			Point p2 = Point( "Point(" + ToString( randint(gen) )+")", p1.GetX() + slide, p1.GetY() );
			Point p3 = Point( "Point(" + ToString( randint(gen) ) + ")", p2.GetX(), p2.GetY() - slide);
			Point p4 = Point( "Point(" + ToString( randint(gen) ) + ")", p3.GetX()-slide, p3.GetY()  );
			Square newsquare( "Square(" + ToString( randint(gen) ) + ")", p1, p2, p3, p4 );
			shape = newsquare;
			break;
		}

		case POLYLINE:
		{
			int quantity = randint(gen);
		
			Polyline newpolyline( "Polyline(" + ToString( randint(gen) )+")" );
			for ( int i = 0; i <= quantity; i++ ) {
				Point  point = Newpoint();
				newpolyline.AddPoint( point );
			}
			shape = newpolyline;
			break;
		}

		case POLYGON:
		{
			int quantity = randint(gen);
			Polygon newpolygon( "Polygon(" + ToString( randint(gen) )+")" );
			for ( int i = 0; i <= quantity; i++ ) {
				Point  point = Newpoint();
				newpolygon.AddPoint( point );
			}
			shape = newpolygon;
			break;
		}
	}
	return shape;
}