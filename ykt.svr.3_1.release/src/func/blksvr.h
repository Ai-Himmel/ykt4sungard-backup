#ifndef _BLKSVR_H_
#define _BLKSVR_H_

typedef struct {
    int systemid;
    void * private_data; // pointer to door_dev_module_t
} ks_blksvr_t;

typedef struct {
    /* 检查时间段的回调函数*/
    int (*check_work_time)(ks_blksvr_t *svr,T_t_device *device);
    /* 检查人员名单的回调函数*/
    int (*check_card_list)(ks_blksvr_t *svr,T_t_device *device);
    /* 检查黑名单的回调函数*/
    int (*check_blksheet)(ks_blksvr_t *svr,T_t_device *device);
    /* 检查节假日的回调函数*/
    int (*check_holiday)(ks_blksvr_t *svr,T_t_device *device);
} door_dev_driver_t;

typedef struct {
    const char *dev_type;
    door_dev_driver_t *driver;
} door_dev_type_t;

typedef struct {
    door_dev_type_t *devs;
    int count;
} door_dev_types_t;

typedef struct _door_manufactor_t {
    int manufactory;
    door_dev_types_t dev_types;
    /* 初始化门禁设备驱动的回调函数*/
    int(*init_manufactory)(ks_blksvr_t *svr,struct _door_manufactor_t *manufactory);
    /* 释放门禁设备驱动的回调函数*/
    int(*uninit_manufactory)(ks_blksvr_t *svr,struct _door_manufactor_t *manufactory);
} door_manufactory_t;

/* 初始化设备驱动*/
#define DEV_MODULE(x) int blk_mod_##x(ks_blksvr_t *svr,door_manufactory_t *manufactory)


#endif // _BLKSVR_H_

