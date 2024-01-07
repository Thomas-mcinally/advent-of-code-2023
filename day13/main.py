def smudges_required_for_valid_palindrome_centered_at(s, l,r):
    smudges = 0
    while l >= 0 and r < len(s):
        if s[l] != s[r]:
            smudges += 1
        l-=1
        r+=1
    return smudges

def score_from_chunk(chunk, score_multiplier):
    ROWS = len(chunk)
    COLS = len(chunk[0])

    score = 0
    for c in range(COLS-1):

        for r in range(ROWS):
            if smudges_required_for_valid_palindrome_centered_at(chunk[r], c, c+1) != 0:
                break
        else:
            score += (c+1) * score_multiplier
    return score


with open("input.txt", "r") as file:
    input = file.read()
    chunks = input.split("\n\n")
    chunks = [chunk.split("\n") for chunk in chunks]

total = 0
for chunk in chunks:
    total += score_from_chunk(chunk, 1)
    
rotated_chunks = [list(zip(*chunk)) for chunk in chunks]
for chunk in rotated_chunks:
    total += score_from_chunk(chunk, 100)

print(f"part1 result: {total}")