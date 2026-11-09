#include "plane.h"

Plane::Plane()
{

}
double Plane::get_hp_rate()
{
    return 100 * health / max_health;
}
