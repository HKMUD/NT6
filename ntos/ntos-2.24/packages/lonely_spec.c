
#include "spec.h"

#ifdef NO_ADD_ACTION
object find_player(string);
#endif

void remove_input_to(void | object);
void set_heartbeat_interval(int);
int query_heartbeat_interval();
string buftostr(buffer);
buffer strtobuf(string);

