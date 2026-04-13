# ncsc210-os-lab-g17
Repository for Group G17's project in the Operating Systems Laboratory (NCSC210) course.

## Team Members
- 24JE0683 - Ria Manu Joseph
- 24JE0684 - S Navya Sai Sree
- 24JE0685 - Samriddhi Singh
- 24JE0686 - Sandeep Kumar
- 24JE0687 - Sangareddygari Ashish Varun Reddy
- 24JE0688 - Sanjib Behera

## Who Did What

- Ria Manu Joseph (24JE0683)
	- [Project 1 - xv6] Implemented user-accessible semaphore syscalls (sem_init, sem_down, sem_up) and validated behavior via semtest.
	- [Project 2] Implemented sh_cat utility with standard input/file handling.

- S Navya Sai Sree (24JE0684)
	- [Project 2] Implemented sh_ls utility for directory listing.

- Samriddhi Singh (24JE0685)
	- [Project 1 - xv6] Modified sendmsg and recvmsg syscalls with per-process message buffer/flag handling and validated via msgtest (parent-child messaging with fork/sendmsg/recvmsg polling).
	- [Project 2] Implemented sh_grep with flags (-n, -i, -v, -c), stdin support, and error handling.

- Sandeep Kumar (24JE0686)
	- [Project 1 - xv6] Enhanced kill syscall into multi-mode behavior (normal, immediate, delayed) with kernel-side process state support and dummy-based testing.
	- [Project 2] Implemented sh_head and sh_tail utilities for first/last n line display.

- Sangareddygari Ashish Varun Reddy (24JE0687)
	- [Project 1 - xv6] Implemented poweroff syscall and user utility to terminate processes, flush logs, and trigger QEMU shutdown.
	- [Project 2] Implemented sh_wc utility supporting line, word, and byte counting with flag-based output.

- Sanjib Behera (24JE0688)
	- [Project 1 - xv6] Implemented getpinfo() syscall and ps user process integration to print process snapshot.
	- [Project 2] Implemented the initial shell and sh_rm utility with file deletion and recursive directory deletion support using -r.

