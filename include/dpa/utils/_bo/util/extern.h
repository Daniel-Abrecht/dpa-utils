
struct dpa_u_bo_unique_hashmap_stats_s {
  size_t empty_count;
  size_t collision_count;
  size_t total_buckets;
  size_t entry_count;
  double load_factor;
};

dpa__u_api extern dpa_u_bo_unique_hashmap_stats_t dpa_u_bo_unique_hashmap_stats(void);
dpa__u_api extern void dpa_u_bo_unique_verify(void);
