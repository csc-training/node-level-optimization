! SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>
!
! SPDX-License-Identifier: MIT

program laplacian
  use iso_fortran_env, only : REAL64
  use omp_lib
  implicit none

  integer, parameter :: dp = REAL64
  real(dp), dimension(:,:), allocatable :: A, L
  real(dp) :: dx, dy, x, y
  real(dp) :: meanL
  integer :: nx, ny, i, j
  integer :: iter
  integer, parameter :: niters=50

  real(dp) :: t0, t1

  nx = 16000
  ny = 16000

  ! Grid spacing
  dx = 1.0/real(nx-1)
  dy = 1.0/real(ny-1)
  ! TODO: allocate matrices
  allocate (A(nx, ny), L(nx, ny))

  ! initialize array A(x,y) = (x^2 + y^2) in the domain [0:1,0:1]
  do j = 1, ny
     do i = 1, nx
        x = (i - 1) * dx
        y = (j - 1) * dy
        A(i,j) =  x**2 + y**2
        L(i,j) = 0.0
     end do
  end do

  t0 = omp_get_wtime()
!$omp parallel private(iter)
  ! Compute Laplacian of A and save it to array L
  do iter = 1, niters
!$omp do
    do j = 2, ny-1
      !$omp simd
      do i = 2, nx-1
        L(i,j) = (A(i-1,j) - 2.0*A(i,j) + A(i+1,j)) / dx**2 + &
             (A(i,j-1) - 2.0*A(i,j) + A(i,j+1)) / dy**2
      end do
    end do
!$omp end do
  end do
!$omp end parallel
  t1 = omp_get_wtime()

  ! check the result
  meanL = 0.0
  do j = 2, ny-1
     do i = 2, nx-1
       meanL = meanL + L(i,j)
     end do
  end do

  meanL = meanL / ((nx - 1) * (ny - 1))


  write(*,*) 'numerical solution', meanL
  write(*,*) 'analytic solution', 4.0

  write(*,*) 'time', t1 - t0


end program laplacian
