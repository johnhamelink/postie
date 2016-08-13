# Postie

Libpostal NIF for Erlang

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
