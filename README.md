# WARNING: this library is not ready for use with anything important yet.

# Postie

[Libpostal](https://github.com/openvenues/libpostal) NIF for Erlang & Elixir

![Postman Pat](http://i.imgur.com/0P0Fe1F.gif)

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
