# Network Device Simulator 
Basic network device that receives data packets, routes them to the correct output port, and efficiently handles congestion using C++.

# Data Structure Used: 
  - **Array:** To store and manage multiple network output ports.
  - **Linked List:** To dynamically store packets in each port's buffer.
  - **Priority Queue:** To schedule and prioritize packet processing based on priority levels.
  - **Stack:** To simulate the processing order and allow rollback in case of congestion or error.
