! SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>
!
! SPDX-License-Identifier: MIT

program matrix_multiply
  use iso_fortran_env, only : REAL64, INT64

  implicit none
  integer, parameter :: dp = REAL64, long = INT64
  real(dp), allocatable, dimension(:,:) :: a, b, c
  character(len=20) :: arg(3)
  integer :: maxiter, N
  integer :: i, iter
  integer, parameter :: block = 10

  integer(kind=long) :: t0, t1, tick
  real(kind=dp) :: r, secs

  if (command_argument_count() /= 2) then
     write(*,*) 'usage: ./matmul number-of-iterations array-size'
     stop
  else
     do i = 1, 2
        call get_command_argument(i, arg(i))
     end do
     read(arg(1),*) maxiter
     read(arg(2),*) N
  end if

  if (mod(N, block) /= 0) then
      write(*,*) 'N must be evenly divisible by block: N=', N, ' block=', block
      stop
  end if

  allocate(a(N, N), b(N, N), c(N, N))

  ! init to some values
  a = 0.5_dp
  b = 0.2_dp

  secs = 0.0_dp
  do iter = 1, maxiter
     call system_clock(count=t0)
     call matmul(a, b, c, N)
     call system_clock(count=t1, count_rate=tick)
     secs = secs + (dble (t1-t0) / dble(tick))
  end do

  write(*,'(A, I0, G10.4,A,G12.6)') &
       'Matrix multiplication , N=', N, 1.0d3*secs/dble(maxiter), ' msec. Check=', &
       c(N,N)


contains

  ! square-matrix matmul
  subroutine matmul(a, b, c, N)
    implicit none
    integer, intent(in) :: N
    real(kind=dp), intent(in) :: a(:,:), b(:,:)
    real(kind=dp), intent(out) :: c(:,:)

    real(kind=dp) :: t(N,N)
    integer :: i, j, k, bi, bj, bk
    integer :: num_blocks

    integer(kind=long) :: t0, t1, tick

    num_blocks = N / block

    t = transpose(a)

    c = 0.0_dp
    ! loop over blocks
    do bj = 0, num_blocks - 1
      do bi = 0, num_blocks - 1
        do bk = 0, num_blocks - 1
          ! loop within blocks
          do j = 1, block
            do i = 1, block
              do k = 1, block
                c(i + bi*block, j + bj*block) = &
                  & c(i + bi*block, j + bj*block) + &
                  & t(k + bk*block, i + bi*block) * b(k + bk*block, j + bj*block)
              end do
            end do
          end do
        end do
      end do
    end do

  end subroutine matmul

end program matrix_multiply

