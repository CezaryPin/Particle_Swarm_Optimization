#ifndef __PSO__STRUCTS__
#define __PSO__STRUCTS__

typedef struct s{
    struct p **probe_list;
    int num_probes;
    double s_best_x;
    double s_best_y;
    double s_best_val;
}swarm;

typedef struct p{
    swarm *my_swarm;
    double weight; //[0,1)
    double c_1;  //self trust
    double c_2;  //trust in swarm
    double r_1;  //rand for it-self
    double r_2;  //rand for group
    double p_best_x,p_best_y,p_best_val; //personal_best_signal
    double pos_x,pos_y; //position
    double v_x,v_y;//speed
}probe;

typedef struct c{
    double w;
    double c_1;
    double r_1;
    double c_2;
    double r_2;
}pso_config;


#endif
