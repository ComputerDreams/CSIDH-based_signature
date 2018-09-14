
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include "u512.h"
#include "fp.h"
#include "mont.h"
#include "mont_own.h"
#include "csidh.h"

void u512_print(u512 const *x)
{
    for (size_t i = 63; i < 64; --i)
        printf("%02hhx", i[(unsigned char *) x->c]);
}

void fp_print(fp const *x)
{
    u512 y;
    fp_dec(&y, x);
    u512_print(&y);
}

int main()
{

    clock_t t0, t1;

    private_key priv_alice, priv_bob;
    public_key pub_alice, pub_bob;
    public_key shared_alice, shared_bob;

    printf("\n");


    t0 = clock();
    csidh_private(&priv_alice);
    t1 = clock();

    printf("Alice's private key   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    for (size_t i = 0; i < sizeof(priv_alice); ++i)
        printf("%02hhx", i[(uint8_t *) &priv_alice]);
    printf("\n\n");

    t0 = clock();
    csidh_private(&priv_bob);
    t1 = clock();

    printf("Bob's private key     (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    for (size_t i = 0; i < sizeof(priv_bob); ++i)
        printf("%02hhx", i[(uint8_t *) &priv_bob]);
    printf("\n\n");

    printf("\n========================================\n");
    printf("\tOriginal");
    printf("\n========================================\n");
    t0 = clock();
    assert(csidh(&pub_alice, &base, &priv_alice)); 
    t1 = clock();

    printf("Alice's public key    (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_alice.A);
    printf("\n\n");

    t0 = clock();
    assert(csidh(&pub_bob, &base, &priv_bob));
    t1 = clock();

    printf("Bob's public key      (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_bob.A);
    printf("\n\n");


    t0 = clock();
    assert(csidh(&shared_alice, &pub_bob, &priv_alice));
    t1 = clock();

    printf("Alice's shared secret (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_alice.A);
    printf("\n\n");

    t0 = clock();
    assert(csidh(&shared_bob, &pub_alice, &priv_bob));
    t1 = clock();

    printf("Bob's shared secret   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_bob.A);
    printf("\n\n");

    printf("    ");
    if (memcmp(&shared_alice, &shared_bob, sizeof(public_key)))
        printf("\x1b[31mNOT EQUAL!\x1b[0m\n");
    else
        printf("\x1b[32mequal.\x1b[0m\n");
    printf("\n");
    
    
    printf("\n========================================\n");
    printf("\tX-Wing");
    printf("\n========================================\n");
    
    t0 = clock();
    assert(csidh_2(&pub_alice, &base, &priv_alice));
    t1 = clock();
    
    printf("Alice's public key    (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_2(&pub_bob, &base, &priv_bob));
    t1 = clock();
    
    printf("Bob's public key      (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_bob.A);
    printf("\n\n");
    
    
    t0 = clock();
    assert(csidh_2(&shared_alice, &pub_bob, &priv_alice));
    t1 = clock();
    
    printf("Alice's shared secret (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_2(&shared_bob, &pub_alice, &priv_bob));
    t1 = clock();
    
    printf("Bob's shared secret   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_bob.A);
    printf("\n\n");
    
    printf("    ");
    if (memcmp(&shared_alice, &shared_bob, sizeof(public_key)))
        printf("\x1b[31mNOT EQUAL!\x1b[0m\n");
    else
        printf("\x1b[32mequal.\x1b[0m\n");
    printf("\n");

    printf("\n");

    printf("\n========================================\n");
    printf("\tX-Wing and torsion");
    printf("\n========================================\n");
    
    t0 = clock();
    assert(csidh_4(&pub_alice, &base, &priv_alice));
    t1 = clock();
    
    printf("Alice's public key    (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_4(&pub_bob, &base, &priv_bob));
    t1 = clock();
    
    printf("Bob's public key      (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_bob.A);
    printf("\n\n");
    
    
    t0 = clock();
    assert(csidh_2(&shared_alice, &pub_bob, &priv_alice));
    t1 = clock();
    
    printf("Alice's shared secret (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_2(&shared_bob, &pub_alice, &priv_bob));
    t1 = clock();
    
    printf("Bob's shared secret   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_bob.A);
    printf("\n\n");
    
    printf("    ");
    if (memcmp(&shared_alice, &shared_bob, sizeof(public_key)))
        printf("\x1b[31mNOT EQUAL!\x1b[0m\n");
    else
        printf("\x1b[32mequal.\x1b[0m\n");
    printf("\n");

    printf("\n");

    printf("\n========================================\n");
    printf("\tReyr-Meyer");
    printf("\n========================================\n");
    
    t0 = clock();
    assert(csidh_MR(&pub_alice, &base, &priv_alice));
    t1 = clock();
    
    printf("Alice's public key    (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_MR(&pub_bob, &base, &priv_bob));
    t1 = clock();
    
    printf("Bob's public key      (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_bob.A);
    printf("\n\n");
    
    
    t0 = clock();
    assert(csidh_MR(&shared_alice, &pub_bob, &priv_alice));
    t1 = clock();
    
    printf("Alice's shared secret (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_MR(&shared_bob, &pub_alice, &priv_bob));
    t1 = clock();
    
    printf("Bob's shared secret   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_bob.A);
    printf("\n\n");
    
    printf("    ");
    if (memcmp(&shared_alice, &shared_bob, sizeof(public_key)))
        printf("\x1b[31mNOT EQUAL!\x1b[0m\n");
    else
        printf("\x1b[32mequal.\x1b[0m\n");
    printf("\n");

    printf("\n");

    printf("\n========================================\n");
    printf("\tReyr-Meyer - torsion");
    printf("\n========================================\n");
    
    t0 = clock();
    assert(csidh_MR(&pub_alice, &base, &priv_alice));
    t1 = clock();
    
    printf("Alice's public key    (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_MR_torsion(&pub_bob, &base, &priv_bob));
    t1 = clock();
    
    printf("Bob's public key      (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&pub_bob.A);
    printf("\n\n");
    
    
    t0 = clock();
    assert(csidh_MR(&shared_alice, &pub_bob, &priv_alice));
    t1 = clock();
    
    printf("Alice's shared secret (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_alice.A);
    printf("\n\n");
    
    t0 = clock();
    assert(csidh_MR(&shared_bob, &pub_alice, &priv_bob));
    t1 = clock();
    
    printf("Bob's shared secret   (%7.3lf ms):\n  ", 1000. * (t1 - t0) / CLOCKS_PER_SEC);
    fp_print(&shared_bob.A);
    printf("\n\n");
    
    printf("    ");
    if (memcmp(&shared_alice, &shared_bob, sizeof(public_key)))
        printf("\x1b[31mNOT EQUAL!\x1b[0m\n");
    else
        printf("\x1b[32mequal.\x1b[0m\n");
    printf("\n");

    printf("\n");
}
