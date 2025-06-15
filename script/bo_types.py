
types={
  "bo": {
    "tags": frozenset({
      frozenset({"SIMPLE"})
    }),
    "conv_macros": False
  },
  "a_bo_unique": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
    }),
    "conv_macros": False
  },
  "a_bo_any": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
      frozenset({"SIMPLE"}),
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_gc": {
    "tags": frozenset({
      frozenset({"UNIQUE"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED"}),
      frozenset({"SIMPLE","UNIQUE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","UNIQUE"}),
      frozenset({"STATIC","SIMPLE","UNIQUE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_refcounted": {
    "tags": frozenset({
      frozenset({"SIMPLE","REFCOUNTED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  },
  "a_bo_hashed": {
    "tags": frozenset({
      frozenset({"SIMPLE","HASHED"}),
      frozenset({"SIMPLE","REFCOUNTED","HASHED"}),
      frozenset({"STATIC","SIMPLE","HASHED"}),
      frozenset({"STATIC","SIMPLE","REFCOUNTED","HASHED"}),
    }),
    "conv_macros": True
  }
}
for name, entry in types.items():
  entry["name"] = name
