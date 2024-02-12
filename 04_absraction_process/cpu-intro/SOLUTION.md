This assignment was about running a bunch of simulation using the process script.

What i learnt:
1. Resource utilization is measured has % of cycles (time) CPU was in use over time passed so far
2. States in which a process can be: READY, RUNNING, BLOCKED (on IO), DONE
3. Switching b/w processes can be SWITCH_ON_IO or SWTICH_ON_COMPLETION, first one is better because it allows better utilization of resources
4. Another strategy was on what do when IO completes, should we immediately swtich to that process or just mark it as ready 
