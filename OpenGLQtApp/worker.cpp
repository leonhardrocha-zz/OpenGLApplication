#include "worker.h"

// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
	tracker.InitInstance();
}
 
// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}
 
// --- PROCESS ---
// Start processing data.
void Worker::process() {
    // allocate resources using new here   
	tracker.PaintEvent(m_message);
    emit finished();
}