def mat_mul(A, B, n):
    C = [[0.0] * n for _ in range(n)]

    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]

    return C

def main():
    import time
    program_start = time.process_time()
    n = 512

    # Initialize matrices A and B without specifying initial values
    A = [[2.0] * n for _ in range(n)]
    B = [[2.0] * n for _ in range(n)]

    # Multiply the matrices
    start = time.process_time()
    C = mat_mul(A, B, n)
    end = time.process_time()

    print("Time taken:", round((end - start) * 1e9), "ns")
    program_end = time.process_time()

    print("Total time taken:", round((program_end - program_start) * 1e9), "ns")


if __name__ == "__main__":
    main()
