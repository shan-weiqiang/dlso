
# summary

1. during build a shared or static lib, unlinked symbols does not influence the success build of the lib; the unresolved symbol will be added into symbol table.
2. if a shared lib or static lib are used and linked during compile time, *ALL* symbols must be fully linked, inlcuding those not used by the main program.
3. above rules is transitive, meaning all the libs used during compile must be fully linked
