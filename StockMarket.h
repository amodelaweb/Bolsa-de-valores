#ifndef __StockMarket_H
#define __StockMarket_H

typedef struct InfBroker
{
    char empresa[20];
    int precio;
    int cantidad;
    char broker[20];
    char tipo[1];
} InfBroker;

#endif // !__StockMarket_H
