#include "erl_nif.h"
#include <string.h>
#include <libpostal/libpostal.h>

/* During the NIF load, also load the libpostal language classifier */
static int load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
  if (!libpostal_setup() || !libpostal_setup_language_classifier() || !libpostal_setup_parser()) {
    exit(EXIT_FAILURE);
  }

  return 0;
}

static void unload(ErlNifEnv* env, void* priv) {
  libpostal_teardown();
  libpostal_teardown_language_classifier();
}

static ERL_NIF_TERM string_to_erl_binary(ErlNifEnv* env, char *str) {
  // Define an erlang binary
  ErlNifBinary binary_output;
  // Figure out how much data it'll carry
  unsigned binary_size = strlen(str);

  // Allocate the correct amount of space for the erlang binary construct
  enif_alloc_binary(binary_size, &binary_output);
  memcpy(binary_output.data, str, binary_size);
  return enif_make_binary(env, &binary_output);
}

static ERL_NIF_TERM string_to_erl_atom(ErlNifEnv* env, char *name) {
  ERL_NIF_TERM atom;
  if (enif_make_existing_atom(env, name, &atom, ERL_NIF_LATIN1)) {
    return atom;
  }
  return enif_make_atom(env, name);
}

static ERL_NIF_TERM parse_address_func(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary in_binary;

  if (!enif_inspect_binary(env, argv[0], &in_binary)) {
    return enif_make_badarg(env);
  }

  char *address = (char*) in_binary.data;

  address_parser_options_t options = get_libpostal_address_parser_default_options();
  address_parser_response_t *parsed = parse_address(address, options);
  ERL_NIF_TERM parsed_address[parsed->num_components];

  for (size_t i = 0; i < parsed->num_components; i++) {
    ERL_NIF_TERM key   = string_to_erl_atom(env, parsed->labels[i]);
    ERL_NIF_TERM value = string_to_erl_binary(env, parsed->components[i]);
    // Return a tuple based on each portion of data
    parsed_address[i] = enif_make_tuple2(env, key, value);
  }

  // Free parse result
  address_parser_response_destroy(parsed);
  return enif_make_list_from_array(env, parsed_address, parsed->num_components);
}

static ERL_NIF_TERM expand_address_func(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary in_binary;

  if (!enif_inspect_binary(env, argv[0], &in_binary)) {
    return enif_make_badarg(env);
  }

  // Retrieve address from binary data
  char *address = (char*) in_binary.data;

  size_t num_expansions;
  normalize_options_t options = get_libpostal_default_options();

  char **expansions = expand_address(address, options, &num_expansions);
  ERL_NIF_TERM converted_expansions[num_expansions];

  for (size_t i = 0; i < num_expansions; i++) {
    // Append the binary to the result array.
    converted_expansions[i] = string_to_erl_binary(env, expansions[i]);
  }

  expansion_array_destroy(expansions, num_expansions);
  return enif_make_list_from_array(env, converted_expansions, num_expansions);
}


/* Let's define the array of ErlNifFunc beforehand.
   This is just an array of 4-element structs that have the name of the function
   in erlang, the arity of the function, the name of the corresponding C
   function, and a flag specifying whether it's a dirty nif or not.
*/
static ErlNifFunc nif_funcs[] = {
/*{erl_function_name, erl_function_arity, c_function,          flags} */
  {"expand_address",  1,                  expand_address_func, 0    },
  {"parse_address",   1,                  parse_address_func,  0    }
};


/* Finally, we call ERL_NIF_INIT, which is a macro, with our Erlang module name,
   the list of function mappings, and 4 pointers to functions: load, reload, upgrade,
   and unload.  The docs specify these functions in detail, but our examples are
   simple so we can ignore them for now.
*/

ERL_NIF_INIT(Elixir.Postie, nif_funcs, &load, NULL, NULL, &unload)
