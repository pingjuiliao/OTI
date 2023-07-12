//===-- sanitizer_platform_interceptors.h -----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines macro telling whether sanitizer tools can/should intercept
// given library functions on a given platform.
//
//===----------------------------------------------------------------------===//
#ifndef SANITIZER_PLATFORM_INTERCEPTORS_H
#define SANITIZER_PLATFORM_INTERCEPTORS_H

#include "sanitizer_glibc_version.h"
#include "sanitizer_internal_defs.h"
#include "sanitizer_platform.h"

#if SANITIZER_POSIX
#define SI_POSIX 1
#else
#define SI_POSIX 0
#endif

#if !SANITIZER_WINDOWS
#define SI_WINDOWS 0
#else
#define SI_WINDOWS 1
#endif

#if SI_WINDOWS && SI_POSIX
#error "Windows is not POSIX!"
#endif

#if SI_POSIX
#include "sanitizer_platform_limits_freebsd.h"
#include "sanitizer_platform_limits_netbsd.h"
#include "sanitizer_platform_limits_posix.h"
#include "sanitizer_platform_limits_solaris.h"
#endif

#if SANITIZER_LINUX && !SANITIZER_ANDROID
#define SI_LINUX_NOT_ANDROID 1
#else
#define SI_LINUX_NOT_ANDROID 0
#endif

#if SANITIZER_GLIBC
#define SI_GLIBC 1
#else
#define SI_GLIBC 0
#endif

#if SANITIZER_ANDROID
#define SI_ANDROID 1
#else
#define SI_ANDROID 0
#endif

#if SANITIZER_FREEBSD
#define SI_FREEBSD 1
#else
#define SI_FREEBSD 0
#endif

#if SANITIZER_NETBSD
#define SI_NETBSD 1
#else
#define SI_NETBSD 0
#endif

#if SANITIZER_LINUX
#define SI_LINUX 1
#else
#define SI_LINUX 0
#endif

#if SANITIZER_APPLE
#define SI_MAC 1
#define SI_NOT_MAC 0
#else
#define SI_MAC 0
#define SI_NOT_MAC 1
#endif

#if SANITIZER_IOS
#define SI_IOS 1
#else
#define SI_IOS 0
#endif

#if SANITIZER_IOSSIM
#define SI_IOSSIM 1
#else
#define SI_IOSSIM 0
#endif

#if SANITIZER_WATCHOS
#define SI_WATCHOS 1
#else
#define SI_WATCHOS 0
#endif

#if SANITIZER_TVOS
#define SI_TVOS 1
#else
#define SI_TVOS 0
#endif

#if SANITIZER_FUCHSIA
#define SI_NOT_FUCHSIA 0
#else
#define SI_NOT_FUCHSIA 1
#endif

#if SANITIZER_SOLARIS
#define SI_SOLARIS 1
#else
#define SI_SOLARIS 0
#endif

#if SANITIZER_SOLARIS32
#define SI_SOLARIS32 1
#else
#define SI_SOLARIS32 0
#endif

#if SANITIZER_POSIX && !SANITIZER_APPLE
#define SI_POSIX_NOT_MAC 1
#else
#define SI_POSIX_NOT_MAC 0
#endif

#if SANITIZER_LINUX && !SANITIZER_FREEBSD
#define SI_LINUX_NOT_FREEBSD 1
#else
#define SI_LINUX_NOT_FREEBSD 0
#endif

#define SANITIZER_INTERCEPT_STRLEN SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRNLEN (SI_NOT_MAC && SI_NOT_FUCHSIA)
#define SANITIZER_INTERCEPT_STRCMP SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRSTR SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRCASESTR SI_POSIX
#define SANITIZER_INTERCEPT_STRTOK SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRCHR SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRCHRNUL SI_POSIX_NOT_MAC
#define SANITIZER_INTERCEPT_STRRCHR SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRSPN SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_STRPBRK SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_TEXTDOMAIN SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_STRCASECMP SI_POSIX
#define SANITIZER_INTERCEPT_MEMSET 1
#define SANITIZER_INTERCEPT_MEMMOVE 1
#define SANITIZER_INTERCEPT_MEMCPY 1
#define SANITIZER_INTERCEPT_MEMCMP SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_BCMP \
  SANITIZER_INTERCEPT_MEMCMP &&  \
      ((SI_POSIX && _GNU_SOURCE) || SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_STRNDUP SI_POSIX
#define SANITIZER_INTERCEPT___STRNDUP SI_GLIBC
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && \
    __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1070
#define SI_MAC_DEPLOYMENT_BELOW_10_7 1
#else
#define SI_MAC_DEPLOYMENT_BELOW_10_7 0
#endif
// memmem on Darwin doesn't exist on 10.6
// FIXME: enable memmem on Windows.
#define SANITIZER_INTERCEPT_MEMMEM (SI_POSIX && !SI_MAC_DEPLOYMENT_BELOW_10_7)
#define SANITIZER_INTERCEPT_MEMCHR SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_MEMRCHR (SI_FREEBSD || SI_LINUX || SI_NETBSD)

#define SANITIZER_INTERCEPT_READ SI_POSIX
#define SANITIZER_INTERCEPT_PREAD SI_POSIX
#define SANITIZER_INTERCEPT_WRITE SI_POSIX
#define SANITIZER_INTERCEPT_PWRITE SI_POSIX

#define SANITIZER_INTERCEPT_FREAD SI_POSIX
#define SANITIZER_INTERCEPT_FWRITE SI_POSIX
#define SANITIZER_INTERCEPT_FGETS SI_POSIX
#define SANITIZER_INTERCEPT_FPUTS SI_POSIX
#define SANITIZER_INTERCEPT_PUTS SI_POSIX

#define SANITIZER_INTERCEPT_PREAD64 (SI_GLIBC || SI_SOLARIS32)
#define SANITIZER_INTERCEPT_PWRITE64 (SI_GLIBC || SI_SOLARIS32)

#define SANITIZER_INTERCEPT_READV SI_POSIX
#define SANITIZER_INTERCEPT_WRITEV SI_POSIX

#define SANITIZER_INTERCEPT_PREADV \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID)
#define SANITIZER_INTERCEPT_PWRITEV SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_PREADV64 SI_GLIBC
#define SANITIZER_INTERCEPT_PWRITEV64 SI_GLIBC

#define SANITIZER_INTERCEPT_PRCTL SI_LINUX

#define SANITIZER_INTERCEPT_LOCALTIME_AND_FRIENDS SI_POSIX
#define SANITIZER_INTERCEPT_STRPTIME SI_POSIX

#define SANITIZER_INTERCEPT_SCANF SI_POSIX
#define SANITIZER_INTERCEPT_ISOC99_SCANF SI_GLIBC

#ifndef SANITIZER_INTERCEPT_PRINTF
#define SANITIZER_INTERCEPT_PRINTF SI_POSIX
#define SANITIZER_INTERCEPT_PRINTF_L (SI_FREEBSD || SI_NETBSD)
#define SANITIZER_INTERCEPT_ISOC99_PRINTF SI_GLIBC
#endif

#define SANITIZER_INTERCEPT___PRINTF_CHK \
  (SANITIZER_INTERCEPT_PRINTF && SI_GLIBC)

#define SANITIZER_INTERCEPT_FREXP SI_NOT_FUCHSIA
#define SANITIZER_INTERCEPT_FREXPF_FREXPL SI_POSIX

#define SANITIZER_INTERCEPT_GETPWNAM_AND_FRIENDS SI_POSIX
#define SANITIZER_INTERCEPT_GETPWNAM_R_AND_FRIENDS \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GETPWENT \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_FGETGRENT_R (SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_FGETPWENT SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_GETPWENT_R \
  (SI_FREEBSD || SI_NETBSD || SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_FGETPWENT_R (SI_FREEBSD || SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_SETPWENT \
  (SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_CLOCK_GETTIME \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX || SI_SOLARIS)
#define SANITIZER_INTERCEPT_CLOCK_GETCPUCLOCKID \
  (SI_LINUX || SI_FREEBSD || SI_NETBSD)
#define SANITIZER_INTERCEPT_GETITIMER SI_POSIX
#define SANITIZER_INTERCEPT_TIME SI_POSIX
#define SANITIZER_INTERCEPT_GLOB (SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GLOB64 SI_GLIBC
#define SANITIZER_INTERCEPT___B64_TO SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_DN_COMP_EXPAND SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_POSIX_SPAWN SI_POSIX
#define SANITIZER_INTERCEPT_WAIT SI_POSIX
#define SANITIZER_INTERCEPT_INET SI_POSIX
#define SANITIZER_INTERCEPT_PTHREAD_GETSCHEDPARAM SI_POSIX
#define SANITIZER_INTERCEPT_GETADDRINFO SI_POSIX
#define SANITIZER_INTERCEPT_GETNAMEINFO SI_POSIX
#define SANITIZER_INTERCEPT_GETSOCKNAME SI_POSIX
#define SANITIZER_INTERCEPT_GETHOSTBYNAME SI_POSIX
#define SANITIZER_INTERCEPT_GETHOSTBYNAME2 SI_POSIX && !SI_SOLARIS
#define SANITIZER_INTERCEPT_GETHOSTBYNAME_R \
  (SI_FREEBSD || SI_LINUX || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GETHOSTBYNAME2_R \
  (SI_FREEBSD || SI_LINUX_NOT_ANDROID)
#define SANITIZER_INTERCEPT_GETHOSTBYADDR_R \
  (SI_FREEBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GETHOSTENT_R (SI_FREEBSD || SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GETSOCKOPT SI_POSIX
#define SANITIZER_INTERCEPT_ACCEPT SI_POSIX
#define SANITIZER_INTERCEPT_ACCEPT4 \
  (SI_LINUX_NOT_ANDROID || SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_PACCEPT SI_NETBSD
#define SANITIZER_INTERCEPT_MODF SI_POSIX
#define SANITIZER_INTERCEPT_RECVMSG SI_POSIX
#define SANITIZER_INTERCEPT_SENDMSG SI_POSIX
#define SANITIZER_INTERCEPT_RECVMMSG SI_LINUX
#define SANITIZER_INTERCEPT_SENDMMSG SI_LINUX
#define SANITIZER_INTERCEPT_SYSMSG SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_GETPEERNAME SI_POSIX
#define SANITIZER_INTERCEPT_IOCTL SI_POSIX
#define SANITIZER_INTERCEPT_INET_ATON SI_POSIX
#define SANITIZER_INTERCEPT_SYSINFO SI_LINUX
#define SANITIZER_INTERCEPT_READDIR SI_POSIX
#define SANITIZER_INTERCEPT_READDIR64 SI_GLIBC || SI_SOLARIS32
#if SI_LINUX_NOT_ANDROID &&                                                \
    (defined(__i386) || defined(__x86_64) || defined(__mips64) ||          \
     defined(__powerpc64__) || defined(__aarch64__) || defined(__arm__) || \
     defined(__s390__) || defined(__loongarch__) || SANITIZER_RISCV64)
#define SANITIZER_INTERCEPT_PTRACE 1
#else
#define SANITIZER_INTERCEPT_PTRACE 0
#endif
#define SANITIZER_INTERCEPT_SETLOCALE SI_POSIX
#define SANITIZER_INTERCEPT_GETCWD SI_POSIX
#define SANITIZER_INTERCEPT_GET_CURRENT_DIR_NAME SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_STRTOIMAX SI_POSIX
#define SANITIZER_INTERCEPT_MBSTOWCS SI_POSIX
#define SANITIZER_INTERCEPT_MBSNRTOWCS \
  (SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_WCSTOMBS SI_POSIX
#define SANITIZER_INTERCEPT_STRXFRM SI_POSIX
#define SANITIZER_INTERCEPT___STRXFRM_L SI_LINUX
#define SANITIZER_INTERCEPT_WCSXFRM SI_POSIX
#define SANITIZER_INTERCEPT___WCSXFRM_L SI_LINUX
#define SANITIZER_INTERCEPT_WCSNRTOMBS \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_WCRTOMB \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_WCTOMB \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_TCGETATTR SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_REALPATH SI_POSIX
#define SANITIZER_INTERCEPT_CANONICALIZE_FILE_NAME (SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_CONFSTR \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_SCHED_GETAFFINITY SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_SCHED_GETPARAM SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_STRERROR SI_POSIX
#define SANITIZER_INTERCEPT_STRERROR_R SI_POSIX
#define SANITIZER_INTERCEPT_XPG_STRERROR_R SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_SCANDIR \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_SCANDIR64 SI_GLIBC || SI_SOLARIS32
#define SANITIZER_INTERCEPT_GETGROUPS SI_POSIX
#define SANITIZER_INTERCEPT_POLL SI_POSIX
#define SANITIZER_INTERCEPT_PPOLL SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_WORDEXP                                          \
  (SI_FREEBSD || SI_NETBSD || (SI_MAC && !SI_IOS) || SI_LINUX_NOT_ANDROID || \
   SI_SOLARIS)
#define SANITIZER_INTERCEPT_SIGWAIT SI_POSIX
#define SANITIZER_INTERCEPT_SIGWAITINFO SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_SIGTIMEDWAIT SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_SIGSETOPS \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_SIGSET_LOGICOPS SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_SIGPENDING SI_POSIX
#define SANITIZER_INTERCEPT_SIGPROCMASK SI_POSIX
#define SANITIZER_INTERCEPT_PTHREAD_SIGMASK SI_POSIX
#define SANITIZER_INTERCEPT_BACKTRACE \
  (SI_FREEBSD || SI_NETBSD || SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_GETMNTENT SI_LINUX
#define SANITIZER_INTERCEPT_GETMNTENT_R SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_STATFS \
  (SI_FREEBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_STATFS64 SI_GLIBC && SANITIZER_HAS_STATFS64
#define SANITIZER_INTERCEPT_STATVFS \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID)
#define SANITIZER_INTERCEPT_STATVFS64 SI_GLIBC
#define SANITIZER_INTERCEPT_INITGROUPS SI_POSIX
#define SANITIZER_INTERCEPT_ETHER_NTOA_ATON SI_POSIX
#define SANITIZER_INTERCEPT_ETHER_HOST \
  (SI_FREEBSD || SI_MAC || SI_LINUX_NOT_ANDROID)
#define SANITIZER_INTERCEPT_ETHER_R (SI_FREEBSD || SI_LINUX_NOT_ANDROID)
#define SANITIZER_INTERCEPT_SHMCTL                                       \
  (((SI_FREEBSD || SI_LINUX_NOT_ANDROID) && SANITIZER_WORDSIZE == 64) || \
   SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_RANDOM_R SI_GLIBC
#define SANITIZER_INTERCEPT_PTHREAD_ATTR_GET SI_POSIX
#define SANITIZER_INTERCEPT_PTHREAD_ATTR_GETINHERITSCHED \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_ATTR_GETAFFINITY_NP SI_GLIBC
#define SANITIZER_INTERCEPT_PTHREAD_GETAFFINITY_NP SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_PTHREAD_ATTR_GET_SCHED SI_POSIX
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETPSHARED \
  (SI_POSIX && !SI_NETBSD)
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETTYPE SI_POSIX
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETPROTOCOL \
  (SI_MAC || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETPRIOCEILING \
  (SI_MAC || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETROBUST \
  (SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_MUTEXATTR_GETROBUST_NP SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_PTHREAD_RWLOCKATTR_GETPSHARED \
  (SI_POSIX && !SI_NETBSD)
#define SANITIZER_INTERCEPT_PTHREAD_RWLOCKATTR_GETKIND_NP SI_GLIBC
#define SANITIZER_INTERCEPT_PTHREAD_CONDATTR_GETPSHARED (SI_POSIX && !SI_NETBSD)
#define SANITIZER_INTERCEPT_PTHREAD_CONDATTR_GETCLOCK \
  (SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_BARRIERATTR_GETPSHARED \
  (SI_LINUX_NOT_ANDROID && !SI_NETBSD)
#define SANITIZER_INTERCEPT_THR_EXIT SI_FREEBSD
#define SANITIZER_INTERCEPT_TMPNAM SI_POSIX
#define SANITIZER_INTERCEPT_TMPNAM_R (SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTSNAME SI_LINUX
#define SANITIZER_INTERCEPT_PTSNAME_R SI_LINUX
#define SANITIZER_INTERCEPT_TTYNAME SI_POSIX
#define SANITIZER_INTERCEPT_TTYNAME_R SI_POSIX
#define SANITIZER_INTERCEPT_TEMPNAM SI_POSIX
#define SANITIZER_INTERCEPT_SINCOS SI_LINUX || SI_SOLARIS
#define SANITIZER_INTERCEPT_REMQUO SI_POSIX
#define SANITIZER_INTERCEPT_REMQUOL (SI_POSIX && !SI_NETBSD)
#define SANITIZER_INTERCEPT_LGAMMA SI_POSIX
#define SANITIZER_INTERCEPT_LGAMMAL (SI_POSIX && !SI_NETBSD)
#define SANITIZER_INTERCEPT_LGAMMA_R (SI_FREEBSD || SI_LINUX || SI_SOLARIS)
#define SANITIZER_INTERCEPT_LGAMMAL_R SI_LINUX_NOT_ANDROID || SI_SOLARIS
#define SANITIZER_INTERCEPT_DRAND48_R SI_GLIBC
#define SANITIZER_INTERCEPT_RAND_R \
  (SI_FREEBSD || SI_NETBSD || SI_MAC || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_ICONV \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)
#define SANITIZER_INTERCEPT_TIMES SI_POSIX

// FIXME: getline seems to be available on OSX 10.7
#define SANITIZER_INTERCEPT_GETLINE \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_SOLARIS)

#define SANITIZER_INTERCEPT__EXIT \
  (SI_LINUX || SI_FREEBSD || SI_NETBSD || SI_MAC || SI_SOLARIS)

#define SANITIZER_INTERCEPT___LIBC_MUTEX SI_NETBSD
#define SANITIZER_INTERCEPT_PTHREAD_SETNAME_NP \
  (SI_FREEBSD || SI_NETBSD || SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_GETNAME_NP \
  (SI_FREEBSD || SI_NETBSD || SI_GLIBC || SI_SOLARIS)

#define SANITIZER_INTERCEPT_TLS_GET_ADDR \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID)

#define SANITIZER_INTERCEPT_LISTXATTR SI_LINUX
#define SANITIZER_INTERCEPT_GETXATTR SI_LINUX
#define SANITIZER_INTERCEPT_GETRESID SI_LINUX
#define SANITIZER_INTERCEPT_GETIFADDRS \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_MAC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_IF_INDEXTONAME \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_MAC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_CAPGET SI_LINUX_NOT_ANDROID
#if SI_LINUX && defined(__arm__)
#define SANITIZER_INTERCEPT_AEABI_MEM 1
#else
#define SANITIZER_INTERCEPT_AEABI_MEM 0
#endif
#define SANITIZER_INTERCEPT___BZERO SI_MAC || SI_GLIBC
#define SANITIZER_INTERCEPT_BZERO SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_FTIME (!SI_FREEBSD && !SI_NETBSD && SI_POSIX)
#define SANITIZER_INTERCEPT_XDR (SI_GLIBC || SI_SOLARIS)
#define SANITIZER_INTERCEPT_XDRREC SI_GLIBC
#define SANITIZER_INTERCEPT_TSEARCH \
  (SI_LINUX_NOT_ANDROID || SI_MAC || SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_LIBIO_INTERNALS SI_GLIBC
#define SANITIZER_INTERCEPT_FOPEN SI_POSIX
#define SANITIZER_INTERCEPT_FOPEN64 (SI_GLIBC || SI_SOLARIS32)
#define SANITIZER_INTERCEPT_OPEN_MEMSTREAM \
  (SI_LINUX_NOT_ANDROID || SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_OBSTACK SI_GLIBC
#define SANITIZER_INTERCEPT_FFLUSH SI_POSIX
#define SANITIZER_INTERCEPT_FCLOSE SI_POSIX

#ifndef SANITIZER_INTERCEPT_DLOPEN_DLCLOSE
#define SANITIZER_INTERCEPT_DLOPEN_DLCLOSE \
  (SI_FREEBSD || SI_NETBSD || SI_LINUX_NOT_ANDROID || SI_MAC || SI_SOLARIS)
#endif

#define SANITIZER_INTERCEPT_GETPASS \
  (SI_LINUX_NOT_ANDROID || SI_MAC || SI_NETBSD)
#define SANITIZER_INTERCEPT_TIMERFD SI_LINUX_NOT_ANDROID

#define SANITIZER_INTERCEPT_MLOCKX SI_POSIX
#define SANITIZER_INTERCEPT_FOPENCOOKIE SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_SEM \
  (SI_LINUX || SI_FREEBSD || SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PTHREAD_SETCANCEL SI_POSIX
#define SANITIZER_INTERCEPT_MINCORE \
  (SI_LINUX || SI_NETBSD || SI_FREEBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_PROCESS_VM_READV SI_LINUX
#define SANITIZER_INTERCEPT_CTERMID \
  (SI_LINUX || SI_MAC || SI_FREEBSD || SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_CTERMID_R (SI_MAC || SI_FREEBSD || SI_SOLARIS)

#define SANITIZER_INTERCEPTOR_HOOKS \
  (SI_LINUX || SI_MAC || SI_WINDOWS || SI_FREEBSD || SI_NETBSD || SI_SOLARIS)
#define SANITIZER_INTERCEPT_RECV_RECVFROM SI_POSIX
#define SANITIZER_INTERCEPT_SEND_SENDTO SI_POSIX
#define SANITIZER_INTERCEPT_EVENTFD_READ_WRITE SI_LINUX

#define SI_STAT_LINUX (SI_LINUX && __GLIBC_PREREQ(2, 33))
#define SANITIZER_INTERCEPT_STAT                                        \
  (SI_FREEBSD || SI_MAC || SI_ANDROID || SI_NETBSD || SI_SOLARIS ||     \
   SI_STAT_LINUX)
#define SANITIZER_INTERCEPT_STAT64 SI_STAT_LINUX && SANITIZER_HAS_STAT64
#define SANITIZER_INTERCEPT_LSTAT (SI_NETBSD || SI_FREEBSD || SI_STAT_LINUX)
#define SANITIZER_INTERCEPT___XSTAT \
  ((!SANITIZER_INTERCEPT_STAT && SI_POSIX) || SI_STAT_LINUX)
#define SANITIZER_INTERCEPT___XSTAT64 SI_GLIBC
#define SANITIZER_INTERCEPT___LXSTAT SANITIZER_INTERCEPT___XSTAT
#define SANITIZER_INTERCEPT___LXSTAT64 SI_GLIBC

#define SANITIZER_INTERCEPT_UTMP \
  (SI_POSIX && !SI_MAC && !SI_FREEBSD && !SI_NETBSD)
#define SANITIZER_INTERCEPT_UTMPX \
  (SI_LINUX_NOT_ANDROID || SI_MAC || SI_FREEBSD || SI_NETBSD)

#define SANITIZER_INTERCEPT_GETLOADAVG \
  (SI_LINUX_NOT_ANDROID || SI_MAC || SI_FREEBSD || SI_NETBSD)

#define SANITIZER_INTERCEPT_MMAP SI_POSIX
#define SANITIZER_INTERCEPT_MMAP64 SI_GLIBC || SI_SOLARIS
#define SANITIZER_INTERCEPT_MALLOPT_AND_MALLINFO (SI_GLIBC || SI_ANDROID)
#define SANITIZER_INTERCEPT_MEMALIGN (!SI_FREEBSD && !SI_MAC && !SI_NETBSD)
#define SANITIZER_INTERCEPT___LIBC_MEMALIGN SI_GLIBC
#define SANITIZER_INTERCEPT_PVALLOC (SI_GLIBC || SI_ANDROID)
#define SANITIZER_INTERCEPT_CFREE (SI_GLIBC && !SANITIZER_RISCV64)
#define SANITIZER_INTERCEPT_REALLOCARRAY SI_POSIX
#define SANITIZER_INTERCEPT_ALIGNED_ALLOC (!SI_MAC)
#define SANITIZER_INTERCEPT_MALLOC_USABLE_SIZE (!SI_MAC && !SI_NETBSD)
#define SANITIZER_INTERCEPT_MCHECK_MPROBE SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_WCSCAT SI_POSIX
#define SANITIZER_INTERCEPT_WCSDUP SI_POSIX
#define SANITIZER_INTERCEPT_SIGNAL_AND_SIGACTION (!SI_WINDOWS && SI_NOT_FUCHSIA)
#define SANITIZER_INTERCEPT_BSD_SIGNAL SI_ANDROID

#define SANITIZER_INTERCEPT_ACCT (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_USER_FROM_UID SI_NETBSD
#define SANITIZER_INTERCEPT_UID_FROM_USER SI_NETBSD
#define SANITIZER_INTERCEPT_GROUP_FROM_GID SI_NETBSD
#define SANITIZER_INTERCEPT_GID_FROM_GROUP SI_NETBSD
#define SANITIZER_INTERCEPT_ACCESS (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_FACCESSAT (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_GETGROUPLIST \
  (SI_NETBSD || SI_FREEBSD || SI_LINUX)
#define SANITIZER_INTERCEPT_STRLCPY \
  (SI_NETBSD || SI_FREEBSD || SI_MAC || SI_ANDROID)

#define SANITIZER_INTERCEPT_NAME_TO_HANDLE_AT SI_LINUX_NOT_ANDROID
#define SANITIZER_INTERCEPT_OPEN_BY_HANDLE_AT SI_LINUX_NOT_ANDROID

#define SANITIZER_INTERCEPT_READLINK SI_POSIX
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && \
    __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 101000
#define SI_MAC_DEPLOYMENT_BELOW_10_10 1
#else
#define SI_MAC_DEPLOYMENT_BELOW_10_10 0
#endif
#define SANITIZER_INTERCEPT_READLINKAT \
  (SI_POSIX && !SI_MAC_DEPLOYMENT_BELOW_10_10)

#define SANITIZER_INTERCEPT_DEVNAME (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_DEVNAME_R (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_FGETLN (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_STRMODE (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_TTYENT (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_TTYENTPATH SI_NETBSD
#define SANITIZER_INTERCEPT_PROTOENT (SI_LINUX || SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_PROTOENT_R SI_GLIBC
#define SANITIZER_INTERCEPT_NETENT (SI_LINUX || SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_SETVBUF \
  (SI_NETBSD || SI_FREEBSD || SI_LINUX || SI_MAC)
#define SANITIZER_INTERCEPT_GETMNTINFO (SI_NETBSD || SI_FREEBSD || SI_MAC)
#define SANITIZER_INTERCEPT_MI_VECTOR_HASH SI_NETBSD
#define SANITIZER_INTERCEPT_GETVFSSTAT SI_NETBSD
#define SANITIZER_INTERCEPT_REGEX (SI_NETBSD || SI_FREEBSD || SI_LINUX)
#define SANITIZER_INTERCEPT_REGEXSUB SI_NETBSD
#define SANITIZER_INTERCEPT_FTS (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_SYSCTL (SI_NETBSD || SI_FREEBSD || SI_MAC)
#define SANITIZER_INTERCEPT_ASYSCTL SI_NETBSD
#define SANITIZER_INTERCEPT_SYSCTLGETMIBINFO SI_NETBSD
#define SANITIZER_INTERCEPT_NL_LANGINFO (SI_NETBSD || SI_FREEBSD || SI_MAC)
#define SANITIZER_INTERCEPT_MODCTL SI_NETBSD
#define SANITIZER_INTERCEPT_CAPSICUM SI_FREEBSD
#define SANITIZER_INTERCEPT_STRTONUM (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_FPARSELN (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_STATVFS1 SI_NETBSD
#define SANITIZER_INTERCEPT_STRTOI SI_NETBSD
#define SANITIZER_INTERCEPT_CAPSICUM SI_FREEBSD
#define SANITIZER_INTERCEPT_SHA1 SI_NETBSD
#define SANITIZER_INTERCEPT_MD4 SI_NETBSD
#define SANITIZER_INTERCEPT_RMD160 SI_NETBSD
#define SANITIZER_INTERCEPT_MD5 (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_FSEEK (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_MD2 SI_NETBSD
#define SANITIZER_INTERCEPT_SHA2 (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_CDB SI_NETBSD
#define SANITIZER_INTERCEPT_VIS (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_POPEN SI_POSIX
#define SANITIZER_INTERCEPT_POPENVE SI_NETBSD
#define SANITIZER_INTERCEPT_PCLOSE SI_POSIX
#define SANITIZER_INTERCEPT_FUNOPEN (SI_NETBSD || SI_FREEBSD)
#define SANITIZER_INTERCEPT_FUNOPEN2 SI_NETBSD
#define SANITIZER_INTERCEPT_GETFSENT (SI_FREEBSD || SI_NETBSD || SI_MAC)
#define SANITIZER_INTERCEPT_ARC4RANDOM (SI_FREEBSD || SI_NETBSD || SI_MAC)
#define SANITIZER_INTERCEPT_FDEVNAME SI_FREEBSD
#define SANITIZER_INTERCEPT_GETUSERSHELL (SI_POSIX && !SI_ANDROID)
#define SANITIZER_INTERCEPT_SL_INIT (SI_FREEBSD || SI_NETBSD)
#define SANITIZER_INTERCEPT_CRYPT (SI_POSIX && !SI_ANDROID)
#define SANITIZER_INTERCEPT_CRYPT_R (SI_LINUX && !SI_ANDROID)

#define SANITIZER_INTERCEPT_GETRANDOM \
  ((SI_LINUX && __GLIBC_PREREQ(2, 25)) || SI_FREEBSD)
#define SANITIZER_INTERCEPT___CXA_ATEXIT SI_NETBSD
#define SANITIZER_INTERCEPT_ATEXIT SI_NETBSD
#define SANITIZER_INTERCEPT_PTHREAD_ATFORK SI_NETBSD
#define SANITIZER_INTERCEPT_GETENTROPY SI_FREEBSD
#define SANITIZER_INTERCEPT_QSORT \
  (SI_POSIX && !SI_IOSSIM && !SI_WATCHOS && !SI_TVOS && !SI_ANDROID)
#define SANITIZER_INTERCEPT_QSORT_R SI_GLIBC
#define SANITIZER_INTERCEPT_BSEARCH \
  (SI_POSIX && !SI_IOSSIM && !SI_WATCHOS && !SI_TVOS && !SI_ANDROID)
// sigaltstack on i386 macOS cannot be intercepted due to setjmp()
// calling it and assuming that it does not clobber registers.
#define SANITIZER_INTERCEPT_SIGALTSTACK \
  (SI_POSIX && !(SANITIZER_APPLE && SANITIZER_I386))
#define SANITIZER_INTERCEPT_UNAME (SI_POSIX && !SI_FREEBSD)
#define SANITIZER_INTERCEPT___XUNAME SI_FREEBSD
#define SANITIZER_INTERCEPT_FLOPEN SI_FREEBSD
#define SANITIZER_INTERCEPT_PROCCTL SI_FREEBSD
#define SANITIZER_INTERCEPT_HEXDUMP SI_FREEBSD

// This macro gives a way for downstream users to override the above
// interceptor macros irrespective of the platform they are on. They have
// to do two things:
// 1. Build compiler-rt with -DSANITIZER_OVERRIDE_INTERCEPTORS.
// 2. Provide a header file named sanitizer_intercept_overriders.h in the
//    include path for their compiler-rt build.
// An example of an overrider for strlen interceptor that one can list in
// sanitizer_intercept_overriders.h is as follows:
//
// #ifdef SANITIZER_INTERCEPT_STRLEN
// #undef SANITIZER_INTERCEPT_STRLEN
// #define SANITIZER_INTERCEPT_STRLEN <value of choice>
// #endif
//
// This "feature" is useful for downstream users who do not want some of
// their libc funtions to be intercepted. They can selectively disable
// interception of those functions.
#ifdef SANITIZER_OVERRIDE_INTERCEPTORS
#include <sanitizer_intercept_overriders.h>
#endif

#endif  // #ifndef SANITIZER_PLATFORM_INTERCEPTORS_H