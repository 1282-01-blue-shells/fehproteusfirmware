#ifndef FEHUTILITY_H
#define FEHUTILITY_H

void Sleep( int msec );
void Sleep( float sec );
void Sleep( double sec );

double TimeNow();
unsigned int seconds();
unsigned long mseconds();
void ResetTime();

#endif // FEHUTILITY_H
