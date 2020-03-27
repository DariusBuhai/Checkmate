//
// Created by Darius Buhai on 3/27/20.
//

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>


#ifndef CHECKMATE_TEMPLATES_H
#define CHECKMATE_TEMPLATES_H

#define POINTS 10
sf::Shape& RoundedRectangle(float x, float y, float rectWidth, float rectHeight, float radius, const sf::Color& Col, float Outline, const sf::Color& OutlineCol)
{
    sf::Shape* rrect = new sf::Shape();
    rrect->SetOutlineWidth(Outline);
    float X=0,Y=0;
    for(int i=0; i<POINTS; i++)
    {
        X+=radius/POINTS;
        Y=sqrt(radius*radius-X*X);
        rrect->AddPoint(X+x+rectWidth-radius,y-Y+radius,Col,OutlineCol);
    }
    Y=0;
    for(int i=0; i<POINTS; i++)
    {
        Y+=radius/POINTS;
        X=sqrt(radius*radius-Y*Y);
        rrect->AddPoint(x+rectWidth+X-radius,y+rectHeight-radius+Y,Col,OutlineCol);
    }
    X=0;
    for(int i=0; i<POINTS; i++)
    {
        X+=radius/POINTS;
        Y=sqrt(radius*radius-X*X);
        rrect->AddPoint(x+radius-X,y+rectHeight-radius+Y,Col,OutlineCol);
    }
    Y=0;
    for(int i=0; i<POINTS; i++)
    {
        Y+=radius/POINTS;
        X=sqrt(radius*radius-Y*Y);
        rrect->AddPoint(x-X+radius,y+radius-Y,Col,OutlineCol);
    }
    return *rrect;

}

#endif //CHECKMATE_TEMPLATES_H
