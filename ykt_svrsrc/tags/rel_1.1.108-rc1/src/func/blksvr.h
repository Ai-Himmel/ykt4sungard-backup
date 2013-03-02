#ifndef _BLKSVR_H_
#define _BLKSVR_H_

typedef struct {
	int systemid;
	void * private_data; // pointer to door_dev_module_t 
}ks_blksvr_t;

typedef struct {
	int (*check_work_time)(ks_blksvr_t *svr,T_t_pif_device *device);
	int (*check_card_list)(ks_blksvr_t *svr,T_t_pif_device *device);
	int (*check_blksheet)(ks_blksvr_t *svr,T_t_pif_device *device);
	int (*check_holiday)(ks_blksvr_t *svr,T_t_pif_device *device);
}door_dev_driver_t;

typedef struct {
	const char *dev_type;
	door_dev_driver_t *driver;
}door_dev_type_t;

typedef struct {
	door_dev_type_t *devs;
	int count;
}door_dev_types_t;

typedef struct _door_manufactor_t{
	int manufactory;
	door_dev_types_t dev_types;
	int(*init_manufactory)(ks_blksvr_t *svr,struct _door_manufactor_t *manufactory);
	int(*uninit_manufactory)(ks_blksvr_t *svr,struct _door_manufactor_t *manufactory);
}door_manufactory_t;

#define DEV_MODULE(x) int blk_mod_##x(ks_blksvr_t *svr,door_manufactory_t *manufactory)


#endif // _BLKSVR_H_

