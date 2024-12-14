create table
    pgn (
        pgn_id integer primary key,
        event text,
        site text,
        date text,
        round text,
        white text,
        black text,
        result text,
        moves text
    )