# WARNING: this library is not ready for use with anything important yet.

# Postie

### A [Libpostal](https://github.com/openvenues/libpostal) NIF for Erlang & Elixir

![Postman Pat](http://i.imgur.com/0P0Fe1F.gif)

## FAQ

### What's Postie for?

Postie is a NIF for Erlang & Elixir that allows you to use [libpostal](https://github.com/openvenues/libpostal)'s natural language processing algorithm to normalise and parse physical addresses. This is useful for matching or filtering addresses in your system.

### What's a NIF?

NIFs (**N**ative **I**mplemented **F**unctions) are one way of integrating external code into Erlang or Elixir. Postie uses the [libpostal](https://github.com/openvenues/libpostal) C bindings to provide an interface you can use in your projects just as if it was a regular Elixir library.

NIFs have some pretty hefty downsides though - if something goes wrong with them they can take down your entire erlang VM (!), and they can negatively effect the performance of your VM's scheduler. You can find out more about that in the [bitwise](https://github.com/vinoski/bitwise) project.

### Why can't I use this in production yet?

Postie is nowhere near stable enough for use in any environment right now:

 - [ ] There seems to be an issue with the conversion between Erlang Binaries and UTF-8 strings
 - [ ] Because libpostal is uses NLP, it's hard to write reliable unit tests (there are some, but they pass randomly right now).
 - [ ] Because of both of these things, Postie isn't on Hex.pm yet.

## Installation

If [available in Hex](https://hex.pm/docs/publish), the package can be installed as:

  1. Add postie to your list of dependencies in `mix.exs`:

        def deps do
          [{:postie, "~> 0.0.1"}]
        end

  2. Ensure postie is started before your application:

        def application do
          [applications: [:postie]]
        end

## Usage

To parse an an address:

    iex(1)> Postie.parse_address("The Book Club 100-106 Leonard St Shoreditch London EC2A 4RH, United Kingdom")
    [house: "the book club", house_number: "100-106", road: "leonard st",
    suburb: "shoreditch", city: "london", postcode: "ec2a 4rh",
    country: "united kingdom"]
    
To expand an address:

    iex(3)> Postie.expand_address("Quatre vingt douze R. de l'Église")
    ["92 rue de l'eglise", "92 r de l'eglise", "92 rue de l eglise",
    "92 rue de 50 eglise", "92 r de l eglise", "92 r de 50 eglise"]
