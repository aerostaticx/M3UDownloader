#include "conversionHandler.h"

ConversionHandler::ConversionHandler(const Library& l) : library(l)
{}

ConversionHandler::~ConversionHandler()
{}

void ConversionHandler::convert()
{
    qInfo() << "HI";
}
